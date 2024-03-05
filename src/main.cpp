#include "SDL2/SDL.h"
#include "Screen.h"

int main(int argc, char *argv[])
{
    Screen screen(64, 32);

    if (screen.init())
    {
        screen.update();
    }

    return 0;
}