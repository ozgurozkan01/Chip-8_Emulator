cmake_minimum_required(VERSION 3.27)
project(Chip_8_Emulator)

set(CMAKE_CXX_STANDARD 17)
set(SDL2_LIB_DIR C:/Users/ozgur/SDL/lib)
set(SDL2_INCLUDE_DIR C:/Users/ozgur/SDL/include)
set(SDL2_LIBRARY C:/Users/ozgur/SDL/bin)

include_directories(${SDL2_INCLUDE_DIR}  ${PROJECT_SOURCE_DIR}/include)

link_directories( ${SDL2_LIB_DIR} )

add_executable(Chip_8_Emulator main.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        mingw32
        SDL2main
        SDL2
)
