#include "ultrasonic.h"
#include <Arduino.h>

float getDistance(int trigPin, int echoPin)
{
    delayMicroseconds(50);
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);
    float distance = duration * 0.034 / 2;

    return distance;
}

int getLevelPercent(int trigPin, int echoPin)
{
    float distance = getDistance(trigPin, echoPin);

    if (distance == 0)
        return -1; // sensor error

    int percent = map(distance, 20, 5, 0, 100);

    percent = constrain(percent, 0, 100);

    return percent;
}