//
// Created by ozgur on 04/03/2024.
//

#ifndef CHIP_8_EMULATOR_CHIP8_H
#define CHIP_8_EMULATOR_CHIP8_H

#include <cstdint>
#include "SDL2/SDL.h"

class RAM;
class Screen;
class ROMReader;
class CPU;
class Audio;

enum class EEmulatorState : uint8_t
{
    RUNNING,
    QUIT,
    PAUSED
};

class Chip8 {
public:
    Chip8(const char *romName);
    ~Chip8();

    bool init();
    bool isRunning();
    void update();

private:
    uint8_t soundTimer;
    uint8_t delayTimer;

    // Components
    RAM* ram;
    Screen* screen;
    ROMReader* rom;
    CPU* cpu;
    Audio* audio;

    EEmulatorState currentState;

    bool* keymap;
    uint16_t *fontSet;
    const uint32_t fontSize = 80;

    void handleInput();
    void updateTimers();
    void loadFonts();
};


#endif //CHIP_8_EMULATOR_CHIP8_H
