//
// Created by ozgur on 07/03/2024.
//

#ifndef CHIP_8_EMULATOR_RAM_H
#define CHIP_8_EMULATOR_RAM_H

#include <cstdint>

class RAM {
public:
    RAM();
private:
    void loadFonts();

    uint8_t memory[4096];
    uint16_t stack[16];
    uint8_t register_V[16];

    const uint32_t fontSize = 80;
    uint16_t *fontSet;

    uint16_t pc; //  which points at the current instruction in memory
    uint16_t I; // which is used to point at locations in memory
};


#endif //CHIP_8_EMULATOR_RAM_H

