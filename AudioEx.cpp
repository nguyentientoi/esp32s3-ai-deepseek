#include "AudioEx.h"
#include <algorithm>
#include <cmath>

AudioEx::AudioEx() : Audio() {}

void AudioEx::setGain(float gain) {
    if (gain < 0.1f) gain = 0.1f;
    if (gain > 4.0f) gain = 4.0f;
    _gain = gain;
}

float AudioEx::getGain() const {
    return _gain;
}

// Hàm xử lý khuếch đại dữ liệu PCM (nếu có thể truy cập buffer)
void AudioEx::processSamples(int16_t* data, size_t len) {
    if (_gain < 1.01f) return;

    for (size_t i = 0; i < len; i++) {
        float sample = data[i] / 32768.0f;
        sample *= _gain;

        // soft clipping (đỡ rè hơn)
        if (sample > 1.0f) sample = 1.0f - 0.1f * (sample - 1.0f);
        if (sample < -1.0f) sample = -1.0f - 0.1f * (sample + 1.0f);

        data[i] = (int16_t)(sample * 32767.0f);
    }
}
