#include "UnitTest.hh"
#include "storage/Storage.hh"
#include <unordered_map>

static std::unordered_map<std::string, std::string> primary_map;
static std::unordered_map<std::string, std::string> secondary_map;
static std::unordered_map<std::string, std::string> teriary_map;

struct PrimaryCache
{
    static Optional<std::string> get(const std::string& key)
    {
        auto p = primary_map.find(key);
        if(p != primary_map.end())
            return p->second;
        return {};
    }

    static void set(const std::string& key, const std::string& val)
    {
        primary_map.erase(key);
        primary_map.insert({key, val});
    }

    static void del(const std::string& key)
    {
        primary_map.erase(key);
    }
};

struct SecondaryCache
{
    static Optional<std::string> get(const std::string& key)
    {
        auto p = secondary_map.find(key);
        if(p != secondary_map.end())
            return p->second;
        return {};
    }

    static void set(const std::string& key, const std::string& val)
    {
        secondary_map.erase(key);
        secondary_map.insert({key, val});
    }

    static void del(const std::string& key)
    {
        secondary_map.erase(key);
    }
};

struct TeriaryCache
{
    static Optional<std::string> get(const std::string& key)
    {
        auto p = teriary_map.find(key);
        if(p != teriary_map.end())
            return p->second;
        return {};
    }

    static void set(const std::string& key, const std::string& val)
    {
        teriary_map.erase(key);
        teriary_map.insert({key, val});
    }

    static void del(const std::string& key)
    {
        teriary_map.erase(key);
    }
};

TEST_CASE(primary_storage_test)
{
    using DB = Storage<PrimaryCache>;
    primary_map.clear();
    /** 基本测试 */
    TEST_CHECK(!DB::get("not exist"));
    /** 测试set */
    DB::set("key1", "val1");
    TEST_CHECK(primary_map.find("key1") != primary_map.end());
    auto res = DB::get("key1");
    TEST_REQUIRE(res);
    TEST_CHECK(*res == "val1");
    /** 测试del */
    DB::del("key1");
    TEST_CHECK(primary_map.find("key1") == primary_map.end());
    TEST_CHECK(!DB::get("key1"));
}

TEST_CASE(secondary_storage_test)
{
    using DB = Storage<PrimaryCache, SecondaryCache>;
    primary_map.clear();
    secondary_map.clear();
    TEST_CHECK(!DB::get("not exist"));
    secondary_map["2lv_key1"] = "2lv_val1";
    TEST_CHECK(secondary_map.find("2lv_key1") != secondary_map.end()
        && primary_map.find("2lv_key1") == primary_map.end());
    auto res = DB::get("2lv_key1");
    TEST_REQUIRE(res);
    TEST_CHECK(*res == "2lv_val1");
    /** 检查secondary到primary的数据传递 */
    TEST_CHECK(primary_map.find("2lv_key1") != primary_map.end());
}

TEST_CASE(teriary_storage_test)
{
    using DB = Storage<PrimaryCache, SecondaryCache, TeriaryCache>;
    primary_map.clear();
    secondary_map.clear();
    teriary_map.clear();
    TEST_CHECK(!DB::get("not exist"));
    secondary_map["2lv_key1"] = "2lv_val1";
    teriary_map["3lv_key1"] = "3lv_val1";
    TEST_CHECK(primary_map.find("2lv_key1") == primary_map.end()
        && secondary_map.find("2lv_key1") != secondary_map.end()
        && teriary_map.find("2lv_key1") == teriary_map.end());
    TEST_CHECK(primary_map.find("3lv_key1") == primary_map.end()
        && secondary_map.find("3lv_key1") == secondary_map.end()
        && teriary_map.find("3lv_key1") != teriary_map.end());
    auto res = DB::get("2lv_key1");
    TEST_CHECK(res && *res == "2lv_val1");
    res = DB::get("3lv_key1");
    TEST_CHECK(res && *res == "3lv_val1");
    /** 检查数据传递 */
    TEST_CHECK(primary_map.find("2lv_key1") != primary_map.end()
        && secondary_map.find("2lv_key1") != secondary_map.end()
        && teriary_map.find("2lv_key1") == teriary_map.end());
    TEST_CHECK(primary_map.find("3lv_key1") != primary_map.end()
        && secondary_map.find("3lv_key1") != secondary_map.end()
        && teriary_map.find("3lv_key1") != teriary_map.end());
    /** 检查修改向高层传递 */
    DB::set("2lv_key1", "2lv_val2");
    TEST_CHECK(primary_map.find("2lv_key1") != primary_map.end()
        && secondary_map.find("2lv_key1") != secondary_map.end()
        && teriary_map.find("2lv_key1") != teriary_map.end());
    res = DB::get("2lv_key1");
    TEST_CHECK(res && *res == "2lv_val2");
    DB::del("3lv_key1");
    TEST_CHECK(!DB::get("3lv_key1"));
    TEST_CHECK(primary_map.find("3lv_key1") == primary_map.end()
        && secondary_map.find("3lv_key1") == secondary_map.end()
        && teriary_map.find("3lv_key1") == teriary_map.end());
    /** 检查单层修改 */
    DB::secondary_storage::del("2lv_key1");
    TEST_CHECK(primary_map.find("2lv_key1") != primary_map.end()
        && secondary_map.find("2lv_key1") == secondary_map.end()
        && teriary_map.find("2lv_key1") != teriary_map.end());
}
