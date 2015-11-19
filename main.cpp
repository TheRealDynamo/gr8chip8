#include <iostream>
#include "SDL.h"
#include "chip8.h"

int main(int argc, char *argv[]) {
   /* Chip8 chip;

    while(1) {
        chip.emulateCycle();
        if (chip.getDrawFlag()) {

        }
    }
*/
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << "";
    }

    return 0;
}