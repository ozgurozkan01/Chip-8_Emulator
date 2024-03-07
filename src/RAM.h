//
// Created by ozgur on 07/03/2024.
//

#ifndef CHIP_8_EMULATOR_RAM_H
#define CHIP_8_EMULATOR_RAM_H

#include <cstdint>

class RAM {
public:
    RAM();
private:
    void loadFonts();

    const uint32_t fontSize = 80;
    uint16_t *fonts;
};


#endif //CHIP_8_EMULATOR_RAM_H
