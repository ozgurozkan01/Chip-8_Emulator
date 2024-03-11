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
    init();
}

void RAM::init()
{
    loadFonts();
}

RAM::~RAM()
{
    delete [] fontSet;
}

void RAM::loadFonts()
{
    /*
     * For 7 number, how to look like this hex code
     * 1111 0000
     * 0001 0000
     * 0010 0000
     * 0100 0000
     * 0100 0000
     *
     * Whole 1's are drawing 7 number
     * */

    // Set fonts
    fontSet = new uint16_t[fontSize]
            {
                    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                    0x20, 0x60, 0x20, 0x20, 0x70, // 1
                    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
            };

    // Load into ram whole this fonts
    memcpy(&memory[0], fontSet, sizeof(fontSet));
}

uint16_t RAM::getMaxRamSize() {return maxRamSize; }
uint8_t *RAM::getMemory() { return memory; }
uint16_t RAM::getBeginningPoint() const { return ramBeginningPoint; }
std::stack<uint16_t>& RAM::getStack() { return stack; }
uint8_t *RAM::getRegisters_V() { return register_V; }