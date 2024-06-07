#include "SDL2/SDL.h"
#include "Chip8.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    Chip8 chip8_Emulator("C:/Users/ozgur/GitHub/Chip-8_Emulator/ROMs/Pong [Paul Vervalin, 1990].ch8");

    if (!chip8_Emulator.init())
    {
        printf("Emulator could not be initialized!\n");
    }

    while (chip8_Emulator.isRunning())
    {
        chip8_Emulator.update();
    }

    return 0;
}