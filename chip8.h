#ifndef CHIP8_H
#define CHIP8_H
#include <cstdint>

#define MEM_SIZE 4096 // 4096(4kb) for memory
#define REG_SIZE 16 // 16 registers
#define STACK_SIZE 16
#define KEY_PAD_SIZE 16
#define FONT_SIZE 80 // Size of Chip8 fontset

class Chip8Stack {
public:
    uint16_t* sp;

    void push(uint16_t value) {
        if (nextSpot_ < STACK_SIZE) {
            stack_[nextSpot_] = value;

            if (nextSpot_ != 0) {
                ++sp;
            }
            ++nextSpot_;

        } else {
            std::cerr << "Error: Stack overflow\n";
        }
    }

    void pop() {
        if (nextSpot_ == 0) {
            --nextSpot_;
            stack_[nextSpot_] = 0;
            --sp;
        } else {
            std::cerr << "Error: Stack is empty\n";
        }
    }

    Chip8Stack()
        : nextSpot_(0) {
            for (int i = 0; i <= STACK_SIZE; ++i) {
                stack_[i] = 0;
                sp = stack_;
            }

        }
private:
    int nextSpot_;
    uint16_t stack_[STACK_SIZE];
};

class Chip8 {
public:

    void loadRom(const std::string& path);
    void emulateCycle();

    Chip8();
private:
    // Stores current opcode
    uint16_t opcode_;
    // Index register 0x000 to 0xFFF
    uint16_t iReg;
    // Program counter 0x000 to 0xFFF
    uint16_t progCount_;
    // Chip8 memory
    uint8_t memory_[MEM_SIZE];
    // General registers V0 to VE
    // VF register is carry flag
    uint8_t vReg_[REG_SIZE];
    // Timer registers that count at 60hz
    uint8_t delayTimer_;
    uint8_t soundTimer_;
    // Stack to remember location before jump
    Chip8Stack stack_;
    // Current state of Hex Keypad (0x0 to 0xF)
    uint8_t keyState_[KEY_PAD_SIZE];
};
#endif //CHIP8_H

