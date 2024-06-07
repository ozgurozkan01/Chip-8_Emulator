//
// Created by ozgur on 04/03/2024.
//

#ifndef CHIP_8_EMULATOR_SCREEN_H
#define CHIP_8_EMULATOR_SCREEN_H

#include "SDL2/SDL.h"

class Screen {
public:

    Screen();
    ~Screen();
    bool init();
    void clear();
    void render();
    void setActiveSprite(class RAM* ram, struct Instructions& instruction, uint16_t I);
    void drawSprite();

private:
    uint32_t foregroundColor;
    uint32_t backgroundColor;

    const int screenWidth = 64;
    const int screenHeight = 32;
    const char* projectName;
    const int gapSize = 2;
    int scaleFactor;
    int hz;

    bool display[64 * 32]; // (0xF00-0xFFF)

    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
};


#endif //CHIP_8_EMULATOR_SCREEN_H
