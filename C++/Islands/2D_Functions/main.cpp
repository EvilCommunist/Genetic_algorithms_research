#include <iostream>
#include "genetic_common.hpp"

int main() {
    GA ga(4, 100, 0.3, 0.7, 20, 150, {-20.0f, 20.0f});
    auto result = ga.run();
    std::cout << result.Point();
}