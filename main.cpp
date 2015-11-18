#include <iostream>
#include "chip8.h"

int main(int argc, char *argv[]) {
    Chip8Stack s;
    Chip8 chip;

    s.push(10);
    std::cout << *(s.sp) << "\n";
    s.push(12);
    s.push(1323);
    std::cout << s.top() << "\n";
    s.pop();
    std::cout << *(s.sp) << "\n";

    return 0;
}