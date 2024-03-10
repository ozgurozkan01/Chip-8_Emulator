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
        ram(new RAM()),
        screen(new Screen()),
        rom(new ROM("C:/Users/ozgur/GitHub/Chip-8_Emulator/ROMs/Chip8 Picture.ch8")),
        cpu(new CPU)
{}

bool Chip8::init()
{
    if (!rom->readRom(ram->getMemory(), ram->getBeginningPoint(), ram->getMaxRamSize()) || !screen->init())
    {
        return false;
    }

    assignKeyMap();
    return true;
}

void Chip8::assignKeyMap()
{
    keymap = new SDL_KeyCode[16]{
            SDLK_1, SDLK_2, SDLK_3, SDLK_4,
            SDLK_q, SDLK_w, SDLK_e, SDLK_r,
            SDLK_a, SDLK_s, SDLK_d, SDLK_f,
            SDLK_z, SDLK_x, SDLK_c, SDLK_v
    };
}

Chip8::~Chip8()
{
    delete [] keymap;
    delete ram;
    delete screen;
}

void Chip8::update()
{
    while (currentState != EEmulatorState::QUIT)
    {
        screen->render();
        cpu->emulateInstructions(ram);
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
            }
        }
    }

}
