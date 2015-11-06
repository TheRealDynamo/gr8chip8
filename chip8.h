#ifndef CHIP8_H
#define CHIP8_H

#define MEMSIZE 4096
#define REGSIZE 16

class Chip8 {
public:
    float version = 0.1;

    void emulateCycle();

private:
    // Stores current opcode
    uint16_t opcode;
    // Index register 0x000 to 0xFFF
    uint16_t iReg;
    // Program register 0x000 to 0xFFF
    uint16_t pc;
    // Chip8 memory
    uint8_t memory[MEMSIZE];
    // General registers V0 to VE
    // 16th register is cary flag
    uint8_t vReg[REGSIZE];

    void init();
};
#endif //CHIP8_H

