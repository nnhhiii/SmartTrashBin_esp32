#ifndef ULTRASONIC_H
#define ULTRASONIC_H

float getDistance(int trigPin, int echoPin);
int getLevelPercent(int trigPin, int echoPin);
int readLevelStable(int trig, int echo);

#endif