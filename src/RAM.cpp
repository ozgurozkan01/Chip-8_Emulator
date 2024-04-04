//
// Created by ozgur on 07/03/2024.
//

#include "RAM.h"
#include <cstring>

RAM::RAM() :
    // First 0x1FF ram locations are for CHIP8 itself
    ramBeginningPoint(0x200)
{
    maxRamSize = sizeof memory - ramBeginningPoint;
}

uint16_t RAM::getMaxRamSize() const {return maxRamSize; }
uint8_t *RAM::getMemory() { return memory; }
uint16_t RAM::getBeginningPoint() const { return ramBeginningPoint; }
std::stack<uint16_t>& RAM::getStack() { return stack; }
uint8_t *RAM::getRegisters_V() { return register_V; }