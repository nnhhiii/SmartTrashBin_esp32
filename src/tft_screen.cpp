#include "tft_screen.h"

TFT_eSPI tft = TFT_eSPI();

void setupTFTScreen()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.println("SMART BIN");
}

void displayData(String type, float confidence, int organic, int inorganic, int recyclable)
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(2);

    tft.setCursor(10, 40);
    tft.print("Type: ");
    tft.println(type);

    if (confidence > 0.8)
        tft.setTextColor(TFT_GREEN);
    else if (confidence > 0.5)
        tft.setTextColor(TFT_YELLOW);
    else
        tft.setTextColor(TFT_RED);

    tft.setCursor(10, 90);
    tft.print("Conf: ");
    tft.print(confidence * 100, 1); // %
    tft.println("%");

    tft.setCursor(10, 120);
    tft.print("Organic: ");
    tft.print(organic);
    tft.println("%");

    tft.setCursor(10, 150);
    tft.print("Inorganic: ");
    tft.print(inorganic);
    tft.println("%");

    tft.setCursor(10, 180);
    tft.print("Recyclable: ");
    tft.print(recyclable);
    tft.println("%");
}