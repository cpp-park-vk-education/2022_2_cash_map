#include <iostream>

#include "lib.hpp"

int main() {
    std::cout << "Client exe" << "\n";
    std::cout << foo() << "\n";
    for (int i = 1; i < 2; ++i) {}
    return 0;
}
