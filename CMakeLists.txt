cmake_minimum_required(VERSION 3.27)
project(Chip_8_Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chip_8_Emulator main.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        mingw32
        SDL2main
        SDL2
)
