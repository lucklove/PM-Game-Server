#include "UnitTest.hh"
#include "storage/SkillDB.hh"

TEST_CASE(skill_storage)
{
    auto s_opt = SkillDB::get(100);
    TEST_REQUIRE(s_opt);
    TEST_CHECK(s_opt->name == "瞬间移动");
    TEST_REQUIRE(SkillDB::secondary_storage::get(100));
    TEST_CHECK(SkillDB::secondary_storage::get(100)->name == "瞬间移动");
    TEST_REQUIRE(SkillDB::primary_storage::get(100));
    TEST_CHECK(SkillDB::primary_storage::get(100)->name == "瞬间移动");
}
