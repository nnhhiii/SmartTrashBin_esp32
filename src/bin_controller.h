#ifndef BIN_CONTROLLER_H
#define BIN_CONTROLLER_H

#include <Arduino.h>

void setupBinController();
void rotateBinBottom(String type);
void openLid();
void checkBins();

#endif