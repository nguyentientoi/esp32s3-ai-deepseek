#pragma once
#include <driver/i2s.h>

class MicInput {
public:
    MicInput(gpio_num_t ws, gpio_num_t sck, gpio_num_t sd);
    bool begin(uint32_t sampleRate = 16000, uint8_t bits = 32);
    size_t readSamples(int16_t* buffer, size_t samples);
    void setGain(float gain);

private:
    gpio_num_t _ws, _sck, _sd;
    float _gain = 1.0f;
};
