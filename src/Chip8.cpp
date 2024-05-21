//
// Created by ozgur on 04/03/2024.
//

#include "Chip8.h"
#include "RAM.h"
#include "Screen.h"
#include "ROM.h"
#include "CPU.h"
#include "Audio.h"

Chip8::Chip8(const char *romName) :
        currentState(EEmulatorState::RUNNING),
        rom(new ROM(romName)),
        cpu(new CPU()),
        ram(new RAM()),
        screen(new Screen()),
        audio(new Audio()),
        soundTimer(0),
        delayTimer(0),
        keymap(new bool[16]{false})
{}

bool Chip8::init()
{
    loadFonts();

    if (!rom->readRom(ram->getMemory(), ram->getBeginningPoint(), ram->getMaxRamSize()) ||
        !screen->init() ||
        !audio->init())
    {
        printf("Chip8 could not be initialized : %s", SDL_GetError());
        return false;
    }

    return true;
}

Chip8::~Chip8()
{
    delete ram;
    delete screen;
    delete audio;
    delete [] fontSet;
}

void Chip8::update()
{
    while (currentState != EEmulatorState::QUIT)
    {
        // ClockRate / 60 minutes = instruction amount in a second (Hz)
        for (uint32_t clock = 0; clock < cpu->getClockRate() / 60; ++clock)
        {
            cpu->emulateInstructions(ram, screen, keymap, soundTimer, delayTimer);
        }
        screen->render();
        processEvent();
        updateTimers();
        SDL_Delay(cpu->getClockRate() / 60);
    }
}

void Chip8::processEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            currentState = EEmulatorState::QUIT;
            return;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    currentState = EEmulatorState::QUIT;
                    return;
                case SDLK_SPACE:
                    currentState = EEmulatorState::PAUSED;
                    return;
                case SDLK_1:
                    keymap[0] = true;
                    break;
                case SDLK_2:
                    keymap[1] = true;
                    break;
                case SDLK_3:
                    keymap[2] = true;
                    break;
                case SDLK_4:
                    keymap[3] = true;
                    break;
                case SDLK_q:
                    keymap[4] = true;
                    break;
                case SDLK_w:
                    keymap[5] = true;
                    break;
                case SDLK_e:
                    keymap[6] = true;
                    break;
                case SDLK_r:
                    keymap[7] = true;
                    break;
                case SDLK_a:
                    keymap[8] = true;
                    break;
                case SDLK_s:
                    keymap[9] = true;
                    break;
                case SDLK_d:
                    keymap[10] = true;
                    break;
                case SDLK_f:
                    keymap[11] = true;
                    break;
                case SDLK_z:
                    keymap[12] = true;
                    break;
                case SDLK_x:
                    keymap[13] = true;
                    break;
                case SDLK_c:
                    keymap[14] = true;
                    break;
                case SDLK_v:
                    keymap[15] = true;
                    break;
            }
        }

        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_1:
                    keymap[0] = false;
                    break;
                case SDLK_2:
                    keymap[1] = false;
                    break;
                case SDLK_3:
                    keymap[2] = false;
                    break;
                case SDLK_4:
                    keymap[3] = false;
                    break;
                case SDLK_q:
                    keymap[4] = false;
                    break;
                case SDLK_w:
                    keymap[5] = false;
                    break;
                case SDLK_e:
                    keymap[6] = false;
                    break;
                case SDLK_r:
                    keymap[7] = false;
                    break;
                case SDLK_a:
                    keymap[8] = false;
                    break;
                case SDLK_s:
                    keymap[9] = false;
                    break;
                case SDLK_d:
                    keymap[10] = false;
                    break;
                case SDLK_f:
                    keymap[11] = false;
                    break;
                case SDLK_z:
                    keymap[12] = false;
                    break;
                case SDLK_x:
                    keymap[13] = false;
                    break;
                case SDLK_c:
                    keymap[14] = false;
                    break;
                case SDLK_v:
                    keymap[15] = false;
                    break;
            }
        }
    }

}

void Chip8::updateTimers()
{
    if (soundTimer > 0)
    {
        soundTimer--;
        audio->beep(0); // Play
    }
    else
    {
        audio->beep(1); // Stop
    }

    if (delayTimer > 0) delayTimer--;
}

void Chip8::loadFonts()
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
    for (int i = 0; i < fontSize; i++)
    {
        ram->getMemory()[i] = fontSet[i];
    }
}