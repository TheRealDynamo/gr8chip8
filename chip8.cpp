#include <iostream>
#include <fstream>
#include <cstdint>
#include "chip8.h"

// Initialize chip8
void init() {

}

void Chip8::loadRom(const char* fileName) {
    // Initialize before loading
    init();

    // Open file for reading in binary
    std::ifstream gameFile;
    gameFile.open(fileName, std::ios::in | std::ios::binary);

    // Load into memory

    gameFile.close();
}

// Take an opcode and run it (Emul8)
void Chip8::emulateCycle() {
    opcode = fetchOpcode(progCount);
}

uint16_t fetchOpcode(uint16_t programCounter) {

}

