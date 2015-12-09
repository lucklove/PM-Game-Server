#include "UnitTest.hh"
#include "storage/MonsterDB.hh"

TEST_CASE(secondary_storage)
{
    using DB = MonsterDB::secondary_storage;
    DB::del(11);
    TEST_CHECK(!DB::get(11));
    Monster m = { 
        11, "test monster", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35, 36 
    };
    DB::set(m.id, m);
    TEST_REQUIRE(DB::get(11));
    TEST_CHECK(DB::get(11)->id == m.id);
    TEST_CHECK(DB::get(11)->ability == m.ability);
    DB::del(m.id);
    TEST_CHECK(!DB::get(m.id));
}
