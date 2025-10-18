#pragma once
#include <Audio.h>

class AudioEx : public Audio {
public:
    AudioEx();
    void setGain(float gain);  // đặt hệ số khuếch đại
    float getGain() const;
protected:
    void processSamples(int16_t* data, size_t len);  // xử lý khuếch đại
private:
    float _gain = 1.0f; // 1.0 = mặc định, >1 = to hơn
};
