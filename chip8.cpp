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
// Take an opcode and run it (Emul8)
void Chip8::emulateCycle() {
    opcode = memory[progCount] << 8 | memory[progCount + 1];
    
    switch(opcode & 0xF000) {
        case (0x0):
                switch (opcode & 0x00FF) {
                        case 0x00E0:
                                // 00EO CLS
                                break;
                        
                        case 0x00EE:
                                // 00EE RET
                                break;
                        
                        default: 
                                // 0nnn SYS addr
                                break;
                }
                break;
                
        case 0x1000: 
                // 1nnn JP addr
                break;
                
        case 0x3000:
                // 3xkk SE Vx, byte
                break;
                
        case 0x4000:
                // 4xkk SNE Vx, byte
                break;
                
        case 0x5000:
                // 5xy0 SE Vx, Vy
                break;
                
        case 0x6000:
                // 6xkk LD Vx, byte
                break;
                
        case 0x7000:
                // 7xkk ADD Vx, byte
                break;
                
        case 0x8000:
                switch (opcode & 0x000F) {
                        case 0x0000:
                                // 
                                break;
                        
                        case 0x0001:
                                // 
                                break;
                        
                        case 0x0002:
                                // 
                                break;
                        
                        case 0x0003:
                                // 
                                break;
                        
                        case 0x0004:
                                // 
                                break;
                        
                        case 0x0005:
                                // 
                                break;
                        
                        case 0x0006:
                                // 
                                break;
                        
                        case 0x0007:
                                // 
                                break;
                        
                        case 0x000E:
                                // 
                                break;
                        
                }
                break;
                
        default:
                std::cerr << "Error opcode not found\n";
                std::cerr << "OPCODE: " << std::hex << opcode << std::dec << "\n";
    }
}
