//
// Created by ozgur on 07/03/2024.
//

#ifndef CHIP_8_EMULATOR_RAM_H
#define CHIP_8_EMULATOR_RAM_H

#include <cstdint>
#include <stack>

class RAM {
public:
    RAM();
    ~RAM();

    uint16_t getMaxRamSize();
    uint8_t* getMemory();
    std::stack<uint16_t>& getStack();
    uint8_t* getRegisters_V();
    [[nodiscard]] uint16_t getBeginningPoint() const;

private:
    uint8_t memory[4096] = {0};
    uint8_t register_V[16]{0};
    std::stack<uint16_t> stack;
    uint16_t *fontSet;

    const uint32_t fontSize = 80;
    uint16_t ramBeginningPoint;
    uint16_t maxRamSize;

    void init();
    void loadFonts();
};


#endif //CHIP_8_EMULATOR_RAM_H

