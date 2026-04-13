#include "camera.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

String esp32camIP = "http://192.168.1.111/capture";

String captureImage()
{
    HTTPClient http;

    http.begin(esp32camIP);

    int httpCode = http.GET();

    if (httpCode > 0)
    {
        String payload = http.getString();
        http.end();
        return payload;
    }

    http.end();
    return "ERROR";
}

WasteInfo getWasteInfo(String json)
{
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, json);

    if (error)
    {
        Serial.println("JSON parse failed!");
        return {"unknown", 0.0};
    }

    String type = doc["type"] | "unknown";
    float confidence = doc["confidence"] | 0.0;

    return {type, confidence};
}