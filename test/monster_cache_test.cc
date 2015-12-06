#include "UnitTest.hh"
#include "storage/MonsterDB.hh"

TEST_CASE(secondary_storage)
{
    using DB = MonsterDB::secondary_storage;
    DB::del(11);
    TEST_CHECK(!DB::get(11));
    Monster m = { 
        11, "test monster", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 
    };
    DB::set(m.pm_ID, m);
    TEST_REQUIRE(DB::get(11));
    TEST_CHECK(DB::get(11)->pm_ID == m.pm_ID);
    TEST_CHECK(DB::get(11)->pm_Ability == m.pm_Ability);
    DB::del(m.pm_ID);
    TEST_CHECK(!DB::get(m.pm_ID));
}
