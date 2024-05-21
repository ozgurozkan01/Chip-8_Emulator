//
// Created by ozgur on 5/20/2024.
//

#ifndef CHIP_8_EMULATOR_AUDIO_H
#define CHIP_8_EMULATOR_AUDIO_H

#include <array>
#include "SDL2/SDL.h"

class Audio {
public:
    Audio();

    ~Audio();

    bool init();

    void beep(int length) const;

private:

    static void callback(void *userdata, Uint8 *streamBuffer, int length);

    SDL_AudioSpec want{}, have{};
    SDL_AudioDeviceID deviceId{};

    int32_t squareWaveFreq{};  // Frequency of square wave sound e.g. 440hz for middle A
    int32_t audioSampleRate{};
    int16_t volume;             // How loud or not is the sound};
};

#endif //CHIP_8_EMULATOR_AUDIO_H
