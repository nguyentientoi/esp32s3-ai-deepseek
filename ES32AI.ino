#include <WiFi.h>
#include "AudioEx.h"
#include "MicInput.h"

const char* ssid = "Minh Hieu_VNPT";
const char* password = "012345678";

#define I2S_BCLK  15
#define I2S_LRC   16
#define I2S_DOUT  7

// Input - INMP441 Mic
#define I2S_WS_IN   4
#define I2S_SCK_IN  5
#define I2S_SD_IN   6

AudioEx audio;
MicInput mic(I2S_WS_IN, I2S_SCK_IN, I2S_SD_IN);

void setup() {
  Serial.begin(115200);
  Serial.println("🔊 ESP32-S3 + MAX98357A + AudioEx");

  WiFi.begin(ssid, password);
  Serial.print("📡 Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected!");
  Serial.println(WiFi.localIP());

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(21);
  audio.setGain(4.0f); // 👈 tăng gấp đôi âm lượng
  audio.connecttohost("http://icecast.radiofrance.fr/franceinfo-midfi.mp3");
}

void loop() {
  audio.loop();
}
