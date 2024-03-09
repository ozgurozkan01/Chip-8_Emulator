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

enum EEmulatorState
{
    RUNNING,
    QUIT,
    PAUSED
};

class Chip8 {
public:

    // Components
    RAM* memory;
    Screen* screen;
    ROM* rom;

    Chip8();
    ~Chip8();

    bool init();
    void update();

private:
    EEmulatorState currentState;

    uint16_t opcode; // operation code
    bool displayRefresh[64*32]; // (0xF00-0xFFF)
    uint8_t pixels[64*32]; // pixel amount

    uint8_t delayTimer;
    uint8_t soundTimer;

    SDL_KeyCode* keymap; // Keys -> 0 - F

    void assignKeyMap();
    void processEvent();
};


#endif //CHIP_8_EMULATOR_CHIP8_H
