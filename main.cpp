#include <iostream>
#include "chip8.h"

int main(int argc, char *argv[]) {
    int a = 327;
    std::cout << a % 10 << "\n";
    std::cout << (a % 100) / 10 << "\n";
    std::cout << (a % 1000) / 100 << "\n";

    return 0;
}