#ifndef TFT_SCREEN_H
#define TFT_SCREEN_H
#include <TFT_eSPI.h>

void setupTFTScreen();
void displayData(String type, float confidence, int organic, int inorganic, int recyclable);
void showSleepScreen();
void showReadyScreen();
void showProcessingScreen();
void showErrorScreen(String message);

#endif