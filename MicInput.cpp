#include "MicInput.h"
#include <cmath>

MicInput::MicInput(gpio_num_t ws, gpio_num_t sck, gpio_num_t sd)
    : _ws(ws), _sck(sck), _sd(sd) {}

bool MicInput::begin(uint32_t sampleRate, uint8_t bits) {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = (int)sampleRate,
        .bits_per_sample = (i2s_bits_per_sample_t)bits,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 6,
        .dma_buf_len = 128,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = _sck,
        .ws_io_num = _ws,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = _sd
    };

    esp_err_t err = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    if (err != ESP_OK) return false;
    err = i2s_set_pin(I2S_NUM_0, &pin_config);
    if (err != ESP_OK) return false;

    return true;
}

size_t MicInput::readSamples(int16_t* buffer, size_t samples) {
    size_t bytesRead = 0;
    i2s_read(I2S_NUM_0, (void*)buffer, samples * sizeof(int16_t), &bytesRead, portMAX_DELAY);

    size_t samplesRead = bytesRead / sizeof(int16_t);
    if (_gain != 1.0f) {
        for (size_t i = 0; i < samplesRead; ++i) {
            float val = buffer[i] * _gain;
            if (val > 32767) val = 32767;
            if (val < -32768) val = -32768;
            buffer[i] = (int16_t)val;
        }
    }
    return samplesRead;
}

void MicInput::setGain(float gain) {
    if (gain < 0.1f) gain = 0.1f;
    if (gain > 8.0f) gain = 8.0f;
    _gain = gain;
}
