//
// Created by ozgur on 07/03/2024.
//

#ifndef CHIP_8_EMULATOR_RAM_H
#define CHIP_8_EMULATOR_RAM_H

#include <cstdint>

class RAM {
public:
    RAM();
    ~RAM();

    uint16_t getMaxRamSize();
    uint8_t* getMemory();
    [[nodiscard]] uint16_t getBeginningPoint() const;
private:
    void init();
    void loadFonts();

    uint8_t memory[4096] = {0};
    uint16_t stack[16];
    uint8_t register_V[16];

    const uint32_t fontSize = 80;
    uint16_t *fontSet;

    const uint16_t ramBeginningPoint;
    uint16_t maxRamSize;
    uint16_t PC; //  Program Counter which points at the current instruction in memory
    uint16_t I; // Index Pointer which is used to point at locations in memory
};


#endif //CHIP_8_EMULATOR_RAM_H

