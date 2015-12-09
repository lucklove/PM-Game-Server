#include "UnitTest.hh"
#include "storage/AioiDB.hh"

TEST_CASE(aioi_db_test)
{
    TEST_CHECK(AioiDB::get(0, 1) == 0);
    TEST_CHECK(AioiDB::get(1, 18) == 0);
    TEST_CHECK(AioiDB::get(1, 14) == 0);
    TEST_CHECK(AioiDB::get(13, 2) == 2);
    TEST_CHECK(AioiDB::get(17, 17) == 0.5);
}
