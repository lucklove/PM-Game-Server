#include "UnitTest.hh"
#include "storage/MonsterDB.hh"

TEST_CASE(persistent_test)
{
    Monster m1 = { 
        11, "test monster", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35, 36 
    };
    m1.id = MonsterDB::insert(m1);
    Optional<Monster> m;
    m = MonsterDB::tertiary_storage::get(m1.id);
    TEST_REQUIRE(m);
    TEST_CHECK(m->id = m1.id && m->name == m1.name && m->ability == m1.ability);
    MonsterDB::update(m1.id, "ability", 11);
    m = MonsterDB::tertiary_storage::get(m1.id);
    TEST_REQUIRE(m);
    TEST_CHECK(m->id = m1.id && m->name == m1.name && m->ability == 11);
    MonsterDB::delete_persistent(m1.id);
    TEST_CHECK(!MonsterDB::tertiary_storage::get(m1.id));
}
