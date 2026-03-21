#ifndef FIREBASE_H
#define FIREBASE_H

#include <Arduino.h>

void sendWasteLog(String type, float confidence);
void updateBinLevel(int organic, int inorganic, int recyclable);
void sendAlert(String compartment, int level);

#endif