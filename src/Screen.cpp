//
// Created by ozgur on 04/03/2024.
//

#include "Screen.h"
#include <cstdio>

Screen::Screen(int _screenWidth, int _screenHeight) :
        screenHeight(_screenHeight),
        screenWidth(_screenWidth),
        projectName("Chip-8 Emulator"),
        windowShouldBeOpen(SDL_TRUE),
        hz(17), // for 60 fps -> 1000 / 60 = 16.66666
        foregroundColor(0xFFFFFFFF), // WHITE (RGBA)
        backgroundColor(0xFFFF00FF) // YELLOW
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

void Screen::update()
{
    while (windowShouldBeOpen)
    {
        processEvent();
        render();
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

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    windowShouldBeOpen = SDL_FALSE;
                    break;
            }
        }
    }
}

void Screen::render()
{
    SDL_Delay(hz); // to set fps

    SDL_RenderClear(renderer); // Clear renderer
    SDL_SetRenderDrawColor(renderer, 0, 255, 255 ,255);
    SDL_RenderPresent(renderer);
}
