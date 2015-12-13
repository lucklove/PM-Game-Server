#include "UnitTest.hh"
#include "storage/DebuffDB.hh"

TEST_CASE(debuff_db_test)
{
    for(size_t i = 1; i < 7; ++i)
        TEST_CHECK(DebuffDB::get(i));
}

TEST_CASE(debuff_db_check_throw)
{
    bool flag = false;

    try
    {
        DebuffDB::get(0);
        TEST_CHECK(false, "should not reach here");
    }
    catch(std::logic_error&)
    {
        flag = true;
    }
    TEST_CHECK(flag);

    flag = false;
    try
    {
        DebuffDB::get(8);
        TEST_CHECK(false, "should not reach here");
    }
    catch(std::logic_error&)
    {
        flag = true;
    }
    TEST_CHECK(flag);
}
