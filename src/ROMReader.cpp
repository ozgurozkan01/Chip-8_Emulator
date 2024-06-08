//
// Created by ozgur on 09/03/2024.
//

#include "ROMReader.h"

ROMReader::ROMReader(const char *romName) : romName(romName) {}

bool ROMReader::readRom(uint8_t* memory, const uint16_t& beginningPoint, const uint16_t& maxRamSize)
{
    // ROM files are binary based files.
    romStream.open(romName, std::ios_base::binary);

    if (!romStream.is_open()) { return false; }

    romStream.seekg(0, std::ios::end);
    const long romSize = romStream.tellg(); // ROM size
    romStream.seekg(std::ios::beg);

    if (romSize > maxRamSize)
    {
        printf("ROM file : %s is bigger than usuable memory.\n", romName);
        return false;
    }

    if (!romStream.read((char*) &memory[beginningPoint], romSize))
    {
        printf("ROM file : %s could not be read properly.\n", romName);
        return false;
    }
    romStream.close();

    return true;
}