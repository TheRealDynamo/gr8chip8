#include <iostream>
#include "chip8.h"

int main(int argc, char *argv[]) {
    Stack x;
    std::cout << x.topValue() << "\n";
    x.push(7);
    std::cout << x.topValue() << "\n";

    x.push(8);
    std::cout << x.topValue() << "\n";

    x.push(9);
    std::cout << x.topValue() << "\n";

    x.pop();
    std::cout << x.topValue() << "\n";


    return 0;
}