//
// Created by ozgur on 04/03/2024.
//

#include "Chip8.h"
#include "RAM.h"
#include "Screen.h"
#include "ROM.h"

Chip8::Chip8() :
    memory(new RAM()),
    screen(new Screen()),
    rom(new ROM(""))
{}

bool Chip8::init()
{
    if (!rom->init() || !screen->init()) return false;

    assignKeyMap();
    return true;
}

void Chip8::assignKeyMap()
{
    /*  KEY MAP ON KEYBOARD
     *  1 2 3 4
     *  Q W E R
     *  A S D F
     *  Z X C V
     */

    keymap = new SDL_KeyCode[16]{
            SDLK_q,
            SDLK_w,
            SDLK_e,
            SDLK_r,
            SDLK_a,
            SDLK_s,
            SDLK_d,
            SDLK_f,
            SDLK_z,
            SDLK_x,
            SDLK_c,
            SDLK_v,
            SDLK_1,
            SDLK_2,
            SDLK_3,
            SDLK_4,
    };
}

Chip8::~Chip8()
{
    delete [] keymap;
    delete memory;
    delete screen;
}

void Chip8::update() const
{
    screen->update();
}

