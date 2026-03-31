#include <M5Unified.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

// 使用するファイル
#include "file07.h"
#include "file08.h"
#include "file09.h"
#include "file10.h"
#include "file11.h"
#include "file12.h"
#include "file13.h"
#include "file14.h"

#define DEFAULT_GAIN 1.0f
#define CONFIG_I2S_BCK_PIN 6
#define CONFIG_I2S_LRCK_PIN 8
#define CONFIG_I2S_DATA_PIN 5
#define ACCEL_THRESHOLD 3.0f
#define LOOP_DELAY 5

AudioGeneratorWAV *wav = nullptr;
AudioFileSourcePROGMEM *file = nullptr;
AudioOutputI2S *out = nullptr;

const unsigned char* wav_data[] = {
  file07, file08, file09, file10,
  file11, file12, file13, file14
};

const uint32_t wav_size[] = {
  sizeof(file07), sizeof(file08), sizeof(file09), sizeof(file10),
  sizeof(file11), sizeof(file12), sizeof(file13), sizeof(file14)
};

const char* patternNames[] = {
  "Pistol", "Machine Gun", "Bazooka", "Tennis",
  "Wooden Bat", "Iron Bat", "Sword Slash", "Sword Obj"
};

int currentIndex = 0;

void showPattern(int index) {
  M5.Display.fillScreen(BLACK);
  M5.Display.setCursor(0, 0);
  M5.Display.setTextSize(2);
  M5.Display.printf("[ %d ] %s\n", index + 1, patternNames[index]);
  M5.Display.println("Trigger: Shake");
}

void playWAV(int index) {
  if (wav && wav->isRunning()) {
    wav->stop();
    delete wav;
    delete file;
  }

  file = new AudioFileSourcePROGMEM(wav_data[index], wav_size[index]);
  out->SetGain(DEFAULT_GAIN);
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  Serial.begin(115200);
  audioLogger = &Serial;

  out = new AudioOutputI2S();
  out->SetPinout(CONFIG_I2S_BCK_PIN, CONFIG_I2S_LRCK_PIN, CONFIG_I2S_DATA_PIN);

  if (!M5.Imu.begin()) {
    M5.Display.println("IMU Init FAILED");
  }

  showPattern(currentIndex);
}

void loop() {
  M5.update();

  // ボタン押下で次のパターンに移動
  if (M5.BtnA.wasPressed()) {
    currentIndex = (currentIndex + 1) % 8;
    showPattern(currentIndex);
  }

  // IMUで再生トリガ
  float ax, ay, az;
  M5.Imu.getAccel(&ax, &ay, &az);
  float acc = sqrt(ax * ax + ay * ay + az * az);

  if (acc > ACCEL_THRESHOLD && (!wav || !wav->isRunning())) {
    playWAV(currentIndex);
  }

  // 再生中処理
  if (wav && wav->isRunning()) {
    if (!wav->loop()) {
      wav->stop();
      delete wav;
      delete file;
      wav = nullptr;
      file = nullptr;
    }
  }

  delay(LOOP_DELAY);
}
