//
// Created by ozgur on 04/03/2024.
//

#include "Chip8.h"
#include "RAM.h"
#include "Screen.h"
#include "ROM.h"
#include "CPU.h"

Chip8::Chip8() :
        currentState(EEmulatorState::RUNNING),
        rom(new ROM(R"(C:\Users\ozgur\GitHub\Chip-8_Emulator\ROMs\BC_test.ch8)")),
        cpu(new CPU),
        ram(new RAM()),
        screen(new Screen()),
        soundTimer(0),
        delayTimer(0)
{}

bool Chip8::init()
{
    if (!rom->readRom(ram->getMemory(), ram->getBeginningPoint(), ram->getMaxRamSize()) ||
        !screen->init())
    {
        return false;
    }

    assignKeyMap();
    return true;
}

void Chip8::assignKeyMap()
{
    keymap = new bool[16]{false};
}

Chip8::~Chip8()
{
    delete ram;
    delete screen;
}

void Chip8::update()
{
    while (currentState != EEmulatorState::QUIT)
    {
        cpu->emulateInstructions(ram, screen, keymap, soundTimer, delayTimer);
        screen->render();
        processEvent();
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
