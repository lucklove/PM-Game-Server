#include "UnitTest.hh"
#include "storage/AioiDB.hh"

TEST_CASE(aioi_db_test)
{
    for(int i = 0; i < 17; ++i)
    {
        for(int j = 0; j < 17; ++j)
            TEST_REQUIRE(AioiDB::get(i + 1, j + 1));
    }
    TEST_CHECK(!AioiDB::get(0, 1));
    TEST_CHECK(!AioiDB::get(1, 18));
    TEST_CHECK(*AioiDB::get(1, 14) == 0);
    TEST_CHECK(*AioiDB::get(13, 2) == 2);
    TEST_CHECK(*AioiDB::get(17, 17) == 0.5);
}
