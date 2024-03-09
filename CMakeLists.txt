cmake_minimum_required(VERSION 3.27)
project(Chip_8_Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chip_8_Emulator
        src/main.cpp
        src/Chip8.cpp
        src/Chip8.h
        src/Screen.cpp
        src/Screen.h
        src/RAM.cpp
        src/RAM.h
        src/ROM.cpp
        src/ROM.h
)

target_link_libraries(
        ${PROJECT_NAME}
        mingw32
        SDL2main
        SDL2
)
