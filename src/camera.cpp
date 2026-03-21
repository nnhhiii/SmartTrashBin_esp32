#include "camera.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

// String esp32camIP = "http://192.168.1.112/capture";

String esp32camIP = "http://192.168.1.105/capture";

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

String getWasteType(String json)
{
    JsonDocument doc;
    deserializeJson(doc, json);

    String type = doc["type"];
    return type;
}