#include "SDL2/SDL.h"
#include "Chip8.h"

int main(int argc, char *argv[])
{
    Chip8 chip8_Emulator;

    if (chip8_Emulator.init())
    {
        chip8_Emulator.update();
    }

    return 0;
}