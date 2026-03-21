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

void displayData(String type, int organic, int inorganic, int recyclable)
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.println("SMART BIN");

    tft.setCursor(10, 40);
    tft.print("Type: ");
    tft.println(type);

    tft.setCursor(10, 80);
    tft.print("Organic: ");
    tft.print(organic);
    tft.println("%");

    tft.setCursor(10, 110);
    tft.print("Inorganic: ");
    tft.print(inorganic);
    tft.println("%");

    tft.setCursor(10, 140);
    tft.print("Recycle: ");
    tft.print(recyclable);
    tft.println("%");

    tft.setCursor(10, 180);
    tft.println("Status: READY");
}