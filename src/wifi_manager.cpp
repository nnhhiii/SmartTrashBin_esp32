#include "wifi_manager.h"
#include <Arduino.h>

// const char *ssid = "SauAn (TRET)";
// const char *password = "Sauan1944@";

const char *ssid = "MrKen";
const char *password = "Ken260814@";

// const char *ssid = "Xiaomi 13";
// const char *password = "12345678";

void connectWifi()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.print("RSSI: ");
    Serial.println(WiFi.RSSI());
}