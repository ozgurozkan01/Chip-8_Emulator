#include "SDL2/SDL.h"
#include "Chip8.h"

int main(int argc, char *argv[])
{
    Chip8 chip8_Emulator("C:/Users/ozgur/GitHub/Chip-8_Emulator/ROMs/Brix [Andreas Gustafsson, 1990].ch8");

    if (chip8_Emulator.init())
    {
        chip8_Emulator.update();
    }

    return 0;
}