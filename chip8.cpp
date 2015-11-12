#include <iostream>
#include <fstream>
#include "chip8.h"

// Font set
uint8_t chip8FontSet[FONT_SIZE] =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

// Initialize chip8
void Chip8::init() {
    for (int i = 0; i < MEM_SIZE; ++i)
        memory[i] = 0;

    // Load font set
    for (int i = 0; i < FONT_SIZE; ++i)
        memory[i] = chip8FontSet[i];

    loadRom("C:\\Users\\Curley\\Desktop\\gr8chip8\\tetris.ch8");
}

void Chip8::loadRom(const std::string& fileName) {
    size_t gameSize;

    // Open file for reading in binary
    std::ifstream gameFile;
    gameFile.open(fileName, std::ios::in | std::ios::binary);
    if (gameFile.is_open()) {
        // Load into memory
        gameFile.seekg(0, std::ios::end);
        gameSize = gameFile.tellg();

        if (gameSize > 0xFFF - 0x200) // Size of game memory
            std::cerr << "Error: File is too large\n";

        char* temp = (char*) &memory[0x200];

        gameFile.seekg(0, std::ios::beg);
        gameFile.read(temp, gameSize);

        gameFile.close();
    } else {
        std::cerr << "Error: File could not be opened\n";
    }


}
/*
// Take an opcode and run it (Emul8)
void Chip8::emulateCycle() {
    opcode = fetchOpcode(progCount);
}

uint16_t fetchOpcode(uint16_t programCounter) {

}
*/
