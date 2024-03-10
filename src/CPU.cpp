//
// Created by ozgur on 09/03/2024.
//

#include "CPU.h"
#include "RAM.h"

CPU::CPU() :
        PC(0x200),
        I(0),
        opcode(0),
        instruction({0,1,2,3,4,5})
{
/*    std::cout << instruction.firstNibble << std::endl;
    std::cout << instruction.NNN << std::endl;
    std::cout << unsigned(instruction.NN) << std::endl;
    std::cout << unsigned(instruction.N) << std::endl;
    std::cout << unsigned(instruction.X) << std::endl;
    std::cout << unsigned(instruction.Y) << std::endl;*/
}

void CPU::emulateInstructions(RAM* ram)
{
    opcode = (ram->getMemory()[PC]) << 8 | (ram->getMemory()[PC+1]); // get next opcode = convert big endian
    //PC += 2; // increase program counter for next instruction
    
    instruction.firstNibble = (opcode >> 12) & 0x0F;
    instruction.NNN = (opcode & 0x0FFF);
    instruction.NN = (opcode & 0x00FF);
    instruction.N = (opcode & 0x000F);
    instruction.X = (opcode >> 8) & 0x0F;
    instruction.Y = (opcode >> 4) & 0x0F;

    switch (instruction.firstNibble)
    {
        case 0x0:
            if (instruction.NNN == 0x0E0){}
            else if (instruction.NNN == 0x0EE){}
            break;
        case 0x1:
            break;
        case 0x2:
            break;
        case 0x3:
            if (ram->getRegisters_V()[instruction.X] == instruction.NN){}
            break;
        case 0x4:
            if (ram->getRegisters_V()[instruction.X] != instruction.NN){}
            break;
        case 0x5:
            if (instruction.N == 0x0 && ram->getRegisters_V()[instruction.X] == ram->getRegisters_V()[instruction.Y]){}
            break;
        case 0x6:
            ram->getRegisters_V()[instruction.X] = instruction.NN;
            break;
        case 0x7:
            ram->getRegisters_V()[instruction.X] += instruction.NN;
            break;
        case 0x8:
            if (instruction.N == 0x0)
            {
                ram->getRegisters_V()[instruction.X] = ram->getRegisters_V()[instruction.Y];
            }
            else if (instruction.N == 0x1)
            {
                ram->getRegisters_V()[instruction.X] |= ram->getRegisters_V()[instruction.Y];
            }
            else if (instruction.N == 0x2)
            {
                ram->getRegisters_V()[instruction.X] &= ram->getRegisters_V()[instruction.Y];
            }
            else if (instruction.N == 0x3)
            {
                ram->getRegisters_V()[instruction.X] ^= ram->getRegisters_V()[instruction.Y];
            }
            else if (instruction.N == 0x4)
            {
                ram->getRegisters_V()[instruction.X] += ram->getRegisters_V()[instruction.Y];
            }
            else if (instruction.N == 0x5)
            {
                ram->getRegisters_V()[instruction.X] -= ram->getRegisters_V()[instruction.Y];
            }
            else if (instruction.N == 0x6)
            {
                ram->getRegisters_V()[instruction.X] >>= ram->getRegisters_V()[instruction.Y];
            }
            else if (instruction.N == 0x7)
            {
                ram->getRegisters_V()[instruction.X] = ram->getRegisters_V()[instruction.Y] - ram->getRegisters_V()[instruction.X];
            }
            else if (instruction.N == 0xE)
            {
                ram->getRegisters_V()[instruction.X] <<= 1;
            }

            break;
        case 0x9:
            if (instruction.N == 0x0 && ram->getRegisters_V()[instruction.X] != ram->getRegisters_V()[instruction.Y]){}
            break;
        case 0xA:
            I = instruction.NNN;
            break;
        case 0xB:
            PC = ram->getRegisters_V()[0] + instruction.NNN;
            break;
        case 0xC:
            ram->getRegisters_V()[instruction.X] = rand() & instruction.NN;
            break;
        case 0xD:
            // Draw
            break;
        case 0xE:
            if (instruction.NN == 0x9E){}
            else if (instruction.NN == 0xA1){}
            break;
        case 0xF:
            if (instruction.NN == 0x07){}
            else if (instruction.NN == 0x0A){}
            else if (instruction.NN == 0x15){}
            else if (instruction.NN == 0x18){}
            else if (instruction.NN == 0x1E){ I = ram->getRegisters_V()[instruction.X]; }
            else if (instruction.NN == 0x29){}
            else if (instruction.NN == 0x33){}
            else if (instruction.NN == 0x55){}
            else if (instruction.NN == 0x65){}
        break;
    }
}