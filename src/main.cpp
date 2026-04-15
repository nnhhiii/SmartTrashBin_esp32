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
SystemState lastState = ERROR; // để chắc chắn vẽ lần đầu

unsigned long lastActivityTime = 0;
const unsigned long SLEEP_TIMEOUT = 10000;
String errorMsg = "";

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

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  esp_deep_sleep_start();
}

void loop()
{
  if (currentState != lastState)
  {
    switch (currentState)
    {
    case READY:
      showReadyScreen();
      break;

    case PROCESSING:
      showProcessingScreen();
      break;

    case SLEEP:
      showSleepScreen();
      break;

    case ERROR:
      showErrorScreen(errorMsg);
      break;
    }

    lastState = currentState;
  }

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

    if (result == "ERROR")
    {
      currentState = ERROR;
      errorMsg = "Camera fail";
      break;
    }

    WasteInfo wasteInfo = getWasteInfo(result);

    if (wasteInfo.type == "unknown" || wasteInfo.confidence < 0.3)
    {
      currentState = ERROR;
      errorMsg = "AI failed";
      break;
    }

    sendWasteLog(wasteInfo.type, wasteInfo.confidence);
    displayData(wasteInfo.type, wasteInfo.confidence, -1, -1, -1);
    rotateBinBottom(wasteInfo.type, wasteInfo.confidence);

    lastActivityTime = millis();
    currentState = READY;
    break;
  }

  case SLEEP:
  {
    Serial.println("Go to sleep...");
    delay(500);

    setupWakeup();
    delay(100);
    enterDeepSleep();
    break;
  }

  case ERROR:
  {
    Serial.println("ERROR");
    delay(3000);
    currentState = READY;
    break;
  }
  }
}
