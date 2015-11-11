#include <iostream>
#include <fstream>
#include "chip8.h"

#define FONT_SIZE 80 // Size of Chip8 font




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

// Implement stack
void Chip8::Chip8Stack::pop() {

}

// Initialize chip8
void Chip8::init() {
    progCount = 0x200; // Set to ROM in memroy

    // Load font set
    for (int i = 0; i <= FONT_SIZE; ++i)
        memory[i] = chip8FontSet[i];
}

void Chip8::loadRom(const std::string &fileName) {
    // Initialize before loading
    init();

    // Open file for reading in binary
    std::ifstream gameFile;
    gameFile.open(fileName, std::ios::in | std::ios::binary);

    // Load into memory

    gameFile.close();
}
/*
// Take an opcode and run it (Emul8)
void Chip8::emulateCycle() {
    opcode = fetchOpcode(progCount);
}

uint16_t fetchOpcode(uint16_t programCounter) {

}
*/
