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
    [[nodiscard]] uint16_t getMaxRamSize() const;
    [[nodiscard]] uint16_t getBeginningPoint() const;
    std::stack<uint16_t>& getStack();
    uint8_t* getMemory();
    uint8_t* getRegisters_V();

private:
    uint8_t memory[4096] = {0};
    uint8_t register_V[16]{0};
    std::stack<uint16_t> stack;
    uint16_t ramBeginningPoint;
    uint16_t maxRamSize;
};


#endif //CHIP_8_EMULATOR_RAM_H

