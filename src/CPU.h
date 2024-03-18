//
// Created by ozgur on 09/03/2024.
//

#ifndef CHIP_8_EMULATOR_CPU_H
#define CHIP_8_EMULATOR_CPU_H

#include <cstdint>
#include <bitset>

struct Instructions
{
    // First nibble always says what kind of instruction it is.
    // But other third can be different
    uint16_t firstNibble;
    uint16_t NNN;   // adress
    uint8_t NN;     // 8 bit constant
    uint8_t N;      // 4 bit constant
    uint8_t X;      // 4 bit register identifier - always second
    uint8_t Y;      // 4 bit refister identifier - always third
};

class CPU {
public:
    CPU();

    void emulateInstructions(class RAM* ram, class Screen* screen,const bool* keymap, uint8_t& soundTimer, uint8_t& delayTimer);
    [[nodiscard]] uint32_t getClockRate() const;
private:
    Instructions instruction;
    uint16_t opcode;
    uint16_t PC; //  Program Counter which points at the current instruction in ram
    uint16_t I; // Index Pointer which is used to point at locations in ram
    uint32_t clockRate;
};


#endif //CHIP_8_EMULATOR_CPU_H
