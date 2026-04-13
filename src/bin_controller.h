#ifndef BIN_CONTROLLER_H
#define BIN_CONTROLLER_H

#include <Arduino.h>

void setupBinController();
void rotateBinBottom(String type, float confidence);
void openLid(String type, float confidence, int organic, int inorganic, int recyclable);
void checkBin(String type, float confidence, int organic, int inorganic, int recyclable);

#endif