#ifndef CHIP8_H
#define CHIP8_H

#define MEM_SIZE 0xFFF // 4096(4kb) for memory
#define REG_SIZE 0xF // 0xF is 15 so 16 registers
#define STACK_SIZE 0xF
#define KEY_PAD_SIZE 0xF


class Chip8 {
public:
    void loadRom();
    void emulateCycle();

private:
    // Stores current opcode
    uint16_t opcode;
    // Index register 0x000 to 0xFFF
    uint16_t iReg;
    // Program register 0x000 to 0xFFF
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

