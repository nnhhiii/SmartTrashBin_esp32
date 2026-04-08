#include "bin_controller.h"
#include "ultrasonic.h"
#include "firebase.h"
#include <Stepper.h>
#include <ESP32Servo.h>
// #include "tft_screen.h"
#include <Preferences.h>

#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25

#define SERVO1_PIN 13
#define SERVO2_PIN 12

#define TRIG_ORGANIC 32
#define ECHO_ORGANIC 33

#define TRIG_INORGANIC 21
#define ECHO_INORGANIC 22

#define TRIG_RECYCLABLE 19
#define ECHO_RECYCLABLE 5

Servo lidServo1, lidServo2;
Preferences prefs;

const int stepsPerRevolution = 2048;
int currentPosition = 0;

Stepper stepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void setupBinController()
{
    prefs.begin("bin", false); // namespace "bin"

    currentPosition = prefs.getInt("pos", 0);

    Serial.print("Loaded position: ");
    Serial.println(currentPosition);

    stepper.setSpeed(10);

    lidServo1.attach(SERVO1_PIN);
    lidServo2.attach(SERVO2_PIN);

    lidServo1.write(0);
    lidServo2.write(180);

    pinMode(TRIG_ORGANIC, OUTPUT);
    pinMode(ECHO_ORGANIC, INPUT);

    pinMode(TRIG_INORGANIC, OUTPUT);
    pinMode(ECHO_INORGANIC, INPUT);

    pinMode(TRIG_RECYCLABLE, OUTPUT);
    pinMode(ECHO_RECYCLABLE, INPUT);
}

void rotateBinBottom(String type)
{
    Serial.println("Rotate to: " + type);

    int targetPosition = 0;
    int level = 0;

    if (type == "organic")
    {
        targetPosition = 0;
        level = getLevelPercent(TRIG_ORGANIC, ECHO_ORGANIC);
    }
    else if (type == "inorganic")
    {
        targetPosition = 682;
        level = getLevelPercent(TRIG_INORGANIC, ECHO_INORGANIC);
    }
    else if (type == "recyclable")
    {
        targetPosition = 1365;
        level = getLevelPercent(TRIG_RECYCLABLE, ECHO_RECYCLABLE);
    }

    if (level < 0)
    {
        Serial.println("Sensor error!");
        return;
    }

    // Nếu thùng đầy
    if (level > 80)
    {
        Serial.println("Bin FULL - cannot open lid");

        sendAlert(type, level);

        return; // dừng lại
    }

    int stepsToMove = targetPosition - currentPosition;

    stepper.step(stepsToMove);

    currentPosition = targetPosition;

    // lưu vào flash (NVS)
    prefs.putInt("pos", currentPosition);

    Serial.print("Saved position: ");
    Serial.println(currentPosition);

    delay(1000);

    openLid();
}

void openLid()
{
    Serial.println("Open lid");

    lidServo1.write(90);
    lidServo2.write(90);

    delay(2000);

    lidServo1.write(0);
    lidServo2.write(180);

    Serial.println("Close lid");

    checkBins();
}

void checkBins()
{
    int organic = getLevelPercent(TRIG_ORGANIC, ECHO_ORGANIC);
    int inorganic = getLevelPercent(TRIG_INORGANIC, ECHO_INORGANIC);
    int recyclable = getLevelPercent(TRIG_RECYCLABLE, ECHO_RECYCLABLE);

    Serial.println("===== BIN LEVEL =====");
    Serial.printf("Organic: %d%%\n", organic);
    Serial.printf("Inorganic: %d%%\n", inorganic);
    Serial.printf("Recyclable: %d%%\n", recyclable);
    Serial.println("=====================");

    delay(500);

    // displayData("Updated", organic, inorganic, recyclable);
    updateBinLevel(organic, inorganic, recyclable);

    if (organic > 80)
        sendAlert("organic", organic);

    if (inorganic > 80)
        sendAlert("inorganic", inorganic);

    if (recyclable > 80)
        sendAlert("recyclable", recyclable);
}