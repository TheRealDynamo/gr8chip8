#ifndef CHIP8_H
#define CHIP8_H
#include <cstdint>

#define MEM_SIZE 4096 // 4096(4kb) for memory
#define REG_SIZE 16 // 16 registers
#define STACK_SIZE 16
#define KEY_PAD_SIZE 16

class Stack {
public:

    uint16_t stack[STACK_SIZE];
    uint8_t top;

    uint16_t topValue() {
        return sp;
    }

    void push(uint16_t value) {
        stack[top] = value;
        sp = stack[top];
        ++top;
    }

    void pop() {
        --top;
        stack[top] = 0;
        sp = stack[top - 1];
    }

    Stack()
        : top(0)
        , sp(0) {
            for (int i = 0; i <= STACK_SIZE; ++i)
                stack[i] = 0;
        }

private:
    uint16_t sp;

};

class Chip8 {
public:
    void loadRom(const std::string &fileName);
    void emulateCycle();

private:
    class Chip8Stack {
    public:
        uint8_t stk[STACK_SIZE];
        int top;

        void push();
        void pop();
    };

    // Stores current opcode
    uint16_t opcode;
    // Index register 0x000 to 0xFFF
    uint16_t iReg;
    // Program counter 0x000 to 0xFFF
    uint16_t progCount;
    // Chip8 memory
    uint8_t memory[MEM_SIZE];
    // General registers V0 to VE
    // VF register is carry flag
    uint8_t vReg[REG_SIZE];
    // Timer registers that count at 60hz
    uint8_t delayTimer;
    uint8_t soundTimer;
    // Stack to remember location before jump
    uint16_t stack[STACK_SIZE];
    // Stack pointer
    uint16_t stackPoint;
    // Current state of Hex Keypad (0x0 to 0xF)
    uint8_t keyState[KEY_PAD_SIZE];

    void init();
};
#endif //CHIP8_H

