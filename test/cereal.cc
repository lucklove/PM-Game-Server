#include "UnitTest.hh"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <string>

struct MyRecord
{
    std::string name;
    int age;
    std::string address;

    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(CEREAL_NVP(name), CEREAL_NVP(age), CEREAL_NVP(address));
    }
};

TEST_CASE(cereal_test)
{
    std::stringstream ss;
    const MyRecord r{"Joshua", 20, "NEU"};
    {
        cereal::JSONOutputArchive output(ss);
        output(CEREAL_NVP(r));
    }
    cereal::JSONInputArchive iarchive(ss);
    MyRecord r2;
    iarchive(r2);
    TEST_CHECK(r2.name == r.name);
    TEST_CHECK(r2.age == r.age);
    TEST_CHECK(r2.address == r.address);
};
