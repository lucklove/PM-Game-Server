#include "UnitTest.hh"
#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
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
/*
    std::stringstream ss;
    const MyRecord r{"Joshua", 20, "NEU"};
    cereal::BinaryOutputArchive output(ss);
    output(r);
    std::cout << ss.str() << std::endl;
    cereal::BinaryInputArchive iarchive(ss);
*/
//    MyRecord r2;
//    iarchive(r2);
          
};
