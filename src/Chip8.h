//
// Created by ozgur on 04/03/2024.
//

#ifndef CHIP_8_EMULATOR_CHIP8_H
#define CHIP_8_EMULATOR_CHIP8_H

#include <cstdint>
#include "SDL2/SDL.h"

class RAM;
class Screen;
class ROM;
class CPU;

enum class EEmulatorState : uint8_t
{
    RUNNING,
    QUIT,
    PAUSED
};

class Chip8 {
public:
    Chip8();
    ~Chip8();

    bool init();
    void update();

private:
    uint8_t soundTimer;
    uint8_t delayTimer;

    // Components
    RAM* ram;
    Screen* screen;
    ROM* rom;
    CPU* cpu;

    EEmulatorState currentState;

    bool* keymap;

    void assignKeyMap();
    void processEvent();
    void updateTimers();
};


#endif //CHIP_8_EMULATOR_CHIP8_H
