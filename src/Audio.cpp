//
// Created by ozgur on 5/20/2024.
//

#include <cstdio>
#include "Audio.h"

Audio::Audio() :
    squareWaveFreq(440),
    audioSampleRate(44100),
    volume(3000)
{
}

bool Audio::init()
{
    want.freq = 44100,
    want.format = AUDIO_S16LSB,
    want.channels = 1,
    want.samples = 512,
    want.callback = callback;
    want.userdata = this;

    deviceId = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);

    if (!deviceId)
    {
        printf("SDL Audio Device could not be created : %s", SDL_GetError());
        return false;
    }

    if ((want.format != have.format) ||
        (want.channels != have.channels))
    {
        SDL_Log("SDL Audio Spec could not be created ? %s\n", SDL_GetError());
        return false;
    }

    return true; // Success
}

Audio::~Audio()
{
    SDL_CloseAudioDevice(deviceId);
}

void Audio::beep(int length) const
{
    SDL_PauseAudioDevice(deviceId, length);
}

void Audio::callback(void *userdata, uint8_t *streamBuffer, int length)
{
    auto * data = static_cast<Audio *>(userdata);
    auto * stream = (int16_t *)streamBuffer;

    static uint32_t index = 0;
    const int32_t halfPeriod = (data->audioSampleRate / data->squareWaveFreq) / 2;

    for (int i = 0; i < length / 2; i++)
    {
        stream[i] = ((index++ / halfPeriod) % 2) ? data->volume : -data->volume;
    }
 }
