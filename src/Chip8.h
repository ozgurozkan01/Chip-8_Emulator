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

enum EEmulatorState
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
    // Components
    RAM* ram;
    Screen* screen;
    ROM* rom;
    CPU* cpu;

    EEmulatorState currentState;

    SDL_KeyCode* keymap;

    void assignKeyMap();
    void processEvent();
};


#endif //CHIP_8_EMULATOR_CHIP8_H
