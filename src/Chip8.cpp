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
        rom(new ROM("C:/Users/ozgur/GitHub/Chip-8_Emulator/ROMs/IBM Logo.ch8")),
        cpu(new CPU),
        ram(new RAM()),
        screen(new Screen())
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
        cpu->emulateInstructions(ram, screen);
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
            }
        }
    }

}
