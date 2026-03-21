#ifndef TFT_SCREEN_H
#define TFT_SCREEN_H
#include <TFT_eSPI.h>

void setupTFTScreen();
void displayData(String type, int organic, int inorganic, int recyclable);

#endif