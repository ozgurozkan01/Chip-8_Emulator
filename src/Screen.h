//
// Created by ozgur on 04/03/2024.
//

#ifndef CHIP_8_EMULATOR_SCREEN_H
#define CHIP_8_EMULATOR_SCREEN_H

#include "SDL2/SDL.h"

class Screen {
public:
    int screenWidth;
    int screenHeight;
    const char* projectName;

    Screen(int _screenWidth, int _screenHeight);
    ~Screen();

    void update();
    bool init();
private:
    uint32_t foregroundColor;
    uint32_t backgroundColor;

    int hz;
    SDL_bool windowShouldBeOpen;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    void processEvent();
    void render();
};


#endif //CHIP_8_EMULATOR_SCREEN_H
