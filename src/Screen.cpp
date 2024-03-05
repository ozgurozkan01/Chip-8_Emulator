//
// Created by ozgur on 04/03/2024.
//

#include "Screen.h"
#include <cstdio>

Screen::Screen(int _screenWidth, int _screenHeight) :
        screenHeight(_screenHeight),
        screenWidth(_screenWidth),
        projectName("Chip-8 Emulator"),
        windowShouldBeOpen(SDL_TRUE)
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
                              screenWidth,
                              screenHeight,
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
        printf("SDL window could not be created : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void Screen::update()
{
    while (windowShouldBeOpen)
    {
        processEvent();
    }
}

void Screen::processEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            windowShouldBeOpen = SDL_FALSE;
        }
    }
}

void Screen::render()
{
    SDL_RenderClear(renderer);

}
