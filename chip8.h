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
    // Stack pointer, points to top item in stack
    uint16_t* sp;

    uint16_t top();

    // Add value to top of stack
    void push(uint16_t value);

    // Remove item from top of stack
    void pop();

    Chip8Stack();
private:
    int nextSpot_;
    uint16_t mainStack_[STACK_SIZE];
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
    uint16_t I_;
    // Program counter 0x000 to 0xFFF
    uint16_t pc_;
    // Chip8 memory
    uint8_t memory_[MEM_SIZE];
    // General registers V0 to VE
    // VF register is carry flag
    uint8_t V_[REG_SIZE];
    // Timer registers that count at 60hz
    uint8_t delayTimer_;
    uint8_t soundTimer_;
    // Stack to remember location before jump
    Chip8Stack stack_;
    // Current state of Hex Keypad (0x0 to 0xF)
    uint8_t keyState_[KEY_PAD_SIZE];

    // Font set
    uint8_t chip8FontSet_[FONT_SIZE] =
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
};
#endif //CHIP8_H

