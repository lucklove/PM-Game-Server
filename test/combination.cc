#include "UnitTest.hh"
#include "utils/combination.hh"
#include <cassert>

TEST_CASE(combination)
{
    int a = 1, b = 2, c = 3, d = 4;
    combinat(std::tuple<int&, int&, int&>(a, b, c), std::tuple<int&>(d), [](int& x, int& y)
    {
        TEST_CHECK(x || y);
        x = 0;
        y = 0;
    });

    combinat(std::vector<int>{a, b}, std::vector<int>{c, d}, [](int x, int y)
    {
        TEST_CHECK(x == 0 && y == 0);
    });
}
