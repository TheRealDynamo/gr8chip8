#include <iostream>
#include "chip8.h"

int main(int argc, char *argv[]) {
    Chip8 chip;

    while(1) {
        chip.emulateCycle();
        if (chip.getDrawFlag()) {

        }
    }

    return 0;
}