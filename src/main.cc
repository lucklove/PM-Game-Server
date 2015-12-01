#include "Random.hh"
#include <iostream>

int main()
{
    std::cout << Random::get(0.1, 1.0) << std::endl;
}
