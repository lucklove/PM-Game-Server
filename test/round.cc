#include "UnitTest.hh"
#include "battle/Round.hh"
#include <vector>

TEST_CASE(round_test)
{
    Round r;
    int res = 0;

    r.onFirstDebuff([&r](int& res)
    {
        ++res;
        r.skip();
    }, res);

    r.onFirstAttack([]
    {
        TEST_CHECK(false);
    });

    r.onLastDebuff([](int& res)
    {
        ++res;
    }, res);

    r.onLastAttack([](int& res)
    {
        ++res;
    }, res);

    r.apply();

    TEST_CHECK(res == 3);
}
