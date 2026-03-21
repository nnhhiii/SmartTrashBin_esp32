#include "firebase.h"
#include <HTTPClient.h>

String firebaseURL = "https://smarttrashbin-20175-default-rtdb.asia-southeast1.firebasedatabase.app/";

void sendWasteLog(String type, float confidence)
{
    HTTPClient http;

    String url = firebaseURL + "/waste_logs.json";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"bin_id\":\"BIN001\",";
    json += "\"waste_type\":\"" + type + "\",";
    json += "\"confidence\":" + String(confidence) + ",";
    json += "\"timestamp\":{ \".sv\": \"timestamp\" }";
    json += "}";

    int response = http.POST(json);

    Serial.print("Firebase response: ");
    Serial.println(response);

    http.end();
}

void updateBinLevel(int organic, int inorganic, int recyclable)
{
    HTTPClient http;

    String url = firebaseURL + "/bins/BIN001.json";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"organic_level\":" + String(organic) + ",";
    json += "\"inorganic_level\":" + String(inorganic) + ",";
    json += "\"recyclable_level\":" + String(recyclable) + ",";
    json += "\"status\":\"ready\",";
    json += "\"is_connected\":true,";
    json += "\"last_update\":{ \".sv\": \"timestamp\" }";
    json += "}";

    int response = http.PATCH(json);

    Serial.print("Update bins response: ");
    Serial.println(response);

    http.end();
}

void sendAlert(String compartment, int level)
{
    HTTPClient http;

    String url = firebaseURL + "/alerts.json";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"bin_id\":\"BIN001\",";
    json += "\"compartment\":\"" + compartment + "\",";
    json += "\"level\":" + String(level) + ",";
    json += "\"sent\":false,";
    json += "\"created_at\":{ \".sv\": \"timestamp\" }";
    json += "}";

    int response = http.POST(json);

    Serial.print("Alert response: ");
    Serial.println(response);

    http.end();
}