#include "UnitTest.hh"
#include "storage/DebuffDB.hh"

TEST_CASE(debuff_db_test)
{
    for(size_t i = 1; i < 7; ++i)
        TEST_CHECK(DebuffDB::get(i));
    TEST_CHECK(!DebuffDB::get(0));
    TEST_CHECK(!DebuffDB::get(7));
}
