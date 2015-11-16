#include <iostream>
#include <fstream>
#include "chip8.h"

// Stack class
uint16_t Chip8Stack::top() {
    return *(sp);
}

void Chip8Stack::push(uint16_t value) {
    if (nextSpot_ < STACK_SIZE) {
        mainStack_[nextSpot_] = value;

        if (nextSpot_ != 0) {
            ++sp;
        }
        ++nextSpot_;

    } else {
        std::cerr << "Error: Stack overflow\n";
    }
}

void Chip8Stack::pop() {
    if (nextSpot_) {
        --nextSpot_;
        mainStack_[nextSpot_] = 0;
        --sp;
    } else {
        std::cerr << "Error: Stack is empty\n";
    }
}

Chip8Stack::Chip8Stack()
    : nextSpot_(0)
    , sp(mainStack_) {
        for (int i = 0; i <= STACK_SIZE; ++i) {
            mainStack_[i] = 0;
        }
    }

// Initialize chip8
Chip8::Chip8()
    : pc_(0x200) // Game memory starts at 0x200
    , opcode_(0) {
        for (int i = 0; i < MEM_SIZE; ++i)
            memory_[i] = 0;

        // Load font set
        for (int i = 0; i < FONT_SIZE; ++i)
            memory_[i] = chip8FontSet_[i];

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
    opcode_ = memory_[pc_] << 8 | memory_[pc_ + 1];
    /* nnn is the address in an opcode
     * x and y are values the correspond with V
     * Ex: x = 1, so Vx is V1
     * kk is a value inside opcode
     * a single n is a nibble */

    uint16_t nnn = opcode_ & 0x0FFF;
    uint16_t x = (opcode_ & 0x0F00) >> 8;
    uint16_t y = (opcode_ & 0x00F0) >> 4;
    uint16_t kk = opcode_ & 0x00FF;
    uint16_t n = opcode_ & 0x000F;

    switch(opcode_ & 0xF000) {
        case 0x0000:
            switch (opcode_ & 0x00FF) {
                case 0x00E0:
                    // 00EO CLS
                    break;

                case 0x00EE:
                    // 00EE RET
                    pc_ = stack_.top();
                    stack_.pop();
                    break;

                default:
                    std::cerr << "Error: opcode not found\n";
                    std::cerr << "OPCODE: " << std::hex << opcode_ << std::dec << "\n";

            break;
        }
                
        case 0x1000:
            // 1nnn JP addr
            nnn = opcode_ & 0x0FFF;
            pc_ = nnn;
            pc_ -= 2;
            break;


        case 0x2000:
            // 2nnn CALL addr
            nnn = opcode_ & 0x0FFF;
            stack_.push(pc_);
            pc_ = nnn;
            pc_ -= 2;
            break;

                
        case 0x3000:
            // 3xkk SE Vx, byte
            if (V_[x] == kk)
                pc_ += 2;
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

                default:
                    std::cerr << "Error: opcode not found\n";
                    std::cerr << "OPCODE: " << std::hex << opcode_ << std::dec << "\n";
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

                default:
                    std::cerr << "Error: opcode not found\n";
                    std::cerr << "OPCODE: " << std::hex << opcode_ << std::dec << "\n";
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

                default:
                    std::cerr << "Error: opcode not found\n";
                    std::cerr << "OPCODE: " << std::hex << opcode_ << std::dec << "\n";
            }
            break;

        default:
            std::cerr << "Error: opcode not found\n";
            std::cerr << "OPCODE: " << std::hex << opcode_ << std::dec << "\n";
    }

    pc_ += 2;
}
