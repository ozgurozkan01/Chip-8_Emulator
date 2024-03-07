//
// Created by ozgur on 04/03/2024.
//

#ifndef CHIP_8_EMULATOR_CHIP8_H
#define CHIP_8_EMULATOR_CHIP8_H

#include <cstdint>

class Chip8 {
public:
    Chip8();

    void init();
private:

    uint16_t opcode; // operation code
    bool displayRefresh[64*32]; // (0xF00-0xFFF)
    uint8_t pixels[64 * 32]; // pixel amount

    uint8_t delayTimer;
    uint8_t soundTimer;
};


#endif //CHIP_8_EMULATOR_CHIP8_H
