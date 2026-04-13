#include <Arduino.h>
#include "bin_controller.h"
#include "wifi_manager.h"
#include "camera.h"
#include "firebase.h"
#include "tft_screen.h"

#define IR_PIN 34

enum SystemState
{
  READY,
  PROCESSING,
  SLEEP,
  ERROR
};

SystemState currentState = READY;
unsigned long lastActivityTime = 0;
const unsigned long SLEEP_TIMEOUT = 30000;

void setup()
{
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);

  setupBinController();
  connectWifi();
  setupTFTScreen();
  lastActivityTime = millis();
}

void setupWakeup()
{
  esp_sleep_enable_ext0_wakeup((gpio_num_t)IR_PIN, 0); // LOW = wakeup
}

void enterDeepSleep()
{
  Serial.println("Deep sleep...");

  delay(100);

  esp_deep_sleep_start();
}

void loop()
{
  switch (currentState)
  {
  case READY:
    if (digitalRead(IR_PIN) == LOW)
    {
      currentState = PROCESSING;
    }
    else if (millis() - lastActivityTime > SLEEP_TIMEOUT)
    {
      currentState = SLEEP;
    }
    break;

  case PROCESSING:
  {
    Serial.println("Processing...");

    String result = captureImage();
    WasteInfo wasteInfo = getWasteInfo(result);

    sendWasteLog(wasteInfo.type, wasteInfo.confidence);

    rotateBinBottom(wasteInfo.type, wasteInfo.confidence);

    lastActivityTime = millis();
    currentState = READY;
    break;
  }

  case SLEEP:
  {
    Serial.println("Go to sleep...");
    setupWakeup();
    delay(100);
    enterDeepSleep();
    break;
  }

  case ERROR:
    delay(2000);
    currentState = READY;
    break;
  }
}
