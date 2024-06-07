//
// Created by ozgur on 04/03/2024.
//

#include "Screen.h"
#include "RAM.h"
#include "CPU.h"
#include <cstdio>
#include <iostream>

Screen::Screen() :
        projectName("Chip-8 Emulator"),
        hz(17), // for 60 fps -> 1000 / 60 = 16.66666
        foregroundColor(0xFFFFFFFF), // WHITE (RGBA)
        backgroundColor(0x000000FF), // YELLOW
        scaleFactor(20)
{}

Screen::~Screen()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Screen::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not be initialized : %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(projectName,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screenWidth * scaleFactor,
                              screenHeight * scaleFactor,
                              SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        printf("SDL window could not be created : %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        printf("SDL renderer could not be created : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                screenWidth,
                                screenHeight);

    if (texture == nullptr)
    {
        printf("SDL texture could not be created : %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void Screen::render()
{
    SDL_Delay(hz); // to set fps
    SDL_RenderClear(renderer);
    drawSprite();
    SDL_RenderPresent(renderer);
}

void Screen::clear()
{
    memset(&display[0], false, sizeof(display));
}

void Screen::setActiveSprite(struct RAM *ram, struct Instructions& instruction, uint16_t I)
{
    auto xCoord = ram->getRegisters_V()[instruction.X] & (screenWidth-1);
    auto yCoord = ram->getRegisters_V()[instruction.Y] & (screenHeight-1);
    const auto originalX = xCoord;

    ram->getRegisters_V()[0xF] = 0;

    for (uint8_t i = 0; i < instruction.N; ++i)
    {
        xCoord = originalX;
        // Get Sprite Data from RAM
        const uint8_t spriteData = ram->getMemory()[I + i];

        for (int j = 7; j >= 0; j--)
        {
            const bool spriteBit = spriteData & (1 << j);

            if (display[xCoord + yCoord * screenWidth] && spriteBit)
            {
                ram->getRegisters_V()[0xF] = 1;
            }

            display[xCoord + yCoord * screenWidth] ^= spriteBit;
            // Stop drawing, if x gets out of screen width
            if (++xCoord >= screenWidth) break;
        }
        // Stop drawing, if y gets out of screen height
        if (++yCoord >= screenHeight) break;
    }
}

void Screen::drawSprite()
{
    uint8_t backgrounRed = (backgroundColor >> 24) & 0xFF;
    uint8_t backgroundGreen = (backgroundColor >> 16) & 0xFF;
    uint8_t backgrounBlue = (backgroundColor >> 8) & 0xFF;
    uint8_t backgroundAlpha = (backgroundColor >> 0) & 0xFF;

    uint8_t foregroundRed = (foregroundColor >> 24) & 0xFF;
    uint8_t foregroundGreen = (foregroundColor >> 16) & 0xFF;
    uint8_t foregroundBlue = (foregroundColor >> 8) & 0xFF;
    uint8_t foregroundAlpha = (foregroundColor >> 0) & 0xFF;

    SDL_Rect rectangle = {0, 0, scaleFactor-gapSize, scaleFactor-gapSize};

    for (int y = 0; y < screenHeight; ++y)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            rectangle.x = (x * scaleFactor) + (gapSize / 2);
            rectangle.y = (y * scaleFactor) + (gapSize / 2);
            // pixel is on, render
            if (display[y * screenWidth + x])
            {
                SDL_SetRenderDrawColor(renderer, foregroundRed, foregroundGreen, foregroundBlue, foregroundAlpha);
                SDL_RenderFillRect(renderer, &rectangle);
            }
                // pixel is off, no render
            else {
                SDL_SetRenderDrawColor(renderer, backgrounRed, backgroundGreen, backgrounBlue, backgroundAlpha);
                SDL_RenderFillRect(renderer, &rectangle);
            }

        }
    }
}
