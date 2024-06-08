//
// Created by ozgur on 09/03/2024.
//

#ifndef CHIP_8_EMULATOR_ROMREADER_H
#define CHIP_8_EMULATOR_ROMREADER_H

#include <fstream>
#include <cstdint>

class ROMReader {
public:
    ROMReader(const char *romName);
    bool readRom(uint8_t* memory, const uint16_t& beginningPoint, const uint16_t& maxSize);
private:

    const char* romName; // Name of currently running rom
    std::ifstream romStream;
};


#endif //CHIP_8_EMULATOR_ROMREADER_H
