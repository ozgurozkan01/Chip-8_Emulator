//
// Created by ozgur on 04/03/2024.
//

#ifndef CHIP_8_EMULATOR_CHIP8_H
#define CHIP_8_EMULATOR_CHIP8_H


class Chip8 {
public:
    Chip8();

    void init();
private:
    unsigned short opcode; // operation code
    unsigned short I; // index register
    unsigned short  pc; // program counter

    unsigned char RAM[4096]; // memory
    unsigned char register_V[16];
    unsigned char pixels[64 * 32]; // pixel amount

    unsigned char delayTimer;
    unsigned char soundTimer;

};


#endif //CHIP_8_EMULATOR_CHIP8_H
