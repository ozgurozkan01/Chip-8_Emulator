//
// Created by ozgur on 09/03/2024.
//

#ifndef CHIP_8_EMULATOR_ROM_H
#define CHIP_8_EMULATOR_ROM_H


class ROM {
public:
    ROM(const char *romName);
    ~ROM();
private:

    const char* romName; // Name of currently running rom
};


#endif //CHIP_8_EMULATOR_ROM_H
