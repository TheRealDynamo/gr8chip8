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
Chip8::Chip8()
    : progCount_(0x200) // Game memory starts at 0x200
    , opcode_(0) {
        for (int i = 0; i < MEM_SIZE; ++i)
            memory_[i] = 0;

        // Load font set
        for (int i = 0; i < FONT_SIZE; ++i)
            memory_[i] = chip8FontSet[i];

        loadRom("C:\\Users\\Curley\\Desktop\\gr8chip8\\tetris.ch8");
    }

// Load game into memory
void Chip8::loadRom(const std::string& fileName) {
    std::ifstream gameFile;
    size_t gameSize;

    // Open file for reading in binary
    gameFile.open(fileName, std::ios::in | std::ios::binary);
    if (gameFile.is_open()) {
        // Get size of file
        gameFile.seekg(0, std::ios::end);
        gameSize = gameFile.tellg();

        // Check if file is too large
        if (gameSize > 0xFFF - 0x200) // Size of game memory
            std::cerr << "Error: File is too large\n";

        gameFile.seekg(0, std::ios::beg);
        //Pointer to memory at location 0x200
        char* temp = (char*) &memory_[0x200];
        // Store into memory
        gameFile.close();
    } else {
        std::cerr << "Error: File could not be opened\n";
    }


}

// Take an opcode and run it (Emul8)
void Chip8::emulateCycle() {
    opcode_ = memory_[progCount_] << 8 | memory_[progCount_ + 1];
    
    switch(opcode_ & 0xF000) {
        case 0x0000:
            switch (opcode_ & 0x00FF) {
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
            switch (opcode_ & 0x000F) {
                case 0x0000:
                    // 8xy0 LD Vx, Vy
                    break;

                case 0x0001:
                    // 8xy1 OR Vx, Vy
                    break;

                case 0x0002:
                    // 8xy2 AND Vx, Vy
                    break;

                case 0x0003:
                    // 8xy3 XOR Vx, Vy
                    break;

                case 0x0004:
                    // 8xy4 ADD Vx, By
                    break;

                case 0x0005:
                    // 8xy5 SUB Vx, Vy
                    break;

                case 0x0006:
                    // 8xy6 SHR Vx {, Vy}
                    break;

                case 0x0007:
                    // 8xy7 SUBN Vx, Vy
                    break;

                case 0x000E:
                    // 8xyE SHL Vx {, Vy}
                    break;
            }
            break;

        case 0x9000:
            // 9xy0 SNE Vx, Vy
            break;

        case 0xA000:
            // Annn LD I, addr
            break;

        case 0xB000:
            // Bnnn JP V0, addr
            break;

        case 0xC000:
            // Cxkk RND Vx, byte
            break;

        case 0xD000:
            // Dxyn DRW Vx, Vy, nibble
            break;

        case 0xE000:
            switch (opcode_ & 0x0FF) {
                case 0x009E:
                    // Ex93 SKP Vx
                    break;

                case 0x00A1:
                    // ExA1 SKNP Vx
                    break;
            }
            break;

        case 0xF000:
            switch (opcode_ & 0x00FF) {
                case 0x0007:
                    // Fx07 LD Vx, DT
                    break;

                case 0x000A:
                    // Fx0A LD Vx, K
                    break;

                case 0x0015:
                    // Fx15 LD DT, Vx
                    break;

                case 0x0018:
                    // Fx18 LD ST, Vx
                    break;

                case 0x001E:
                    // Fx1E ADD I, Vx
                    break;

                case 0x0029:
                    // Fx29 LD F, Vx
                    break;

                case 0x0033:
                    // Fx33 LD B, Vx
                    break;

                case 0x0055:
                    // Fx55 LD [I], Vx
                    break;

                case 0x0065:
                    // Fx65 LD Vx, [I]
                    break;
            }
            break;
        default:
            std::cerr << "Error: opcode not found\n";
            std::cerr << "OPCODE: " << std::hex << opcode_ << std::dec << "\n";
    }
}
