#include "UnitTest.hh"
#include "storage/MonsterDB.hh"

TEST_CASE(persistent_test)
{
    Monster m1 = { 
        11, "test monster", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 
    };
    m1.pm_ID = MonsterDB::insert(m1);
    Optional<Monster> m;
    m = MonsterDB::tertiary_storage::get(m1.pm_ID);
    TEST_REQUIRE(m);
    TEST_CHECK(m->pm_ID = m1.pm_ID && m->pm_Name == m1.pm_Name && m->pm_Ability == m1.pm_Ability);
    MonsterDB::delete_persistent(m1.pm_ID);
    TEST_CHECK(!MonsterDB::tertiary_storage::get(m1.pm_ID));
}
