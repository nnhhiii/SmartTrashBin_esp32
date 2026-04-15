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
    tft.print(confidence * 100, 1);
    tft.println("%");

    // reset màu
    tft.setTextColor(TFT_WHITE);

    // Organic
    tft.setCursor(10, 120);
    tft.print("Organic: ");
    if (organic >= 0)
        tft.print(organic);
    else
        tft.print("--");
    tft.println("%");

    // Inorganic
    tft.setCursor(10, 150);
    tft.print("Inorganic: ");
    if (inorganic >= 0)
        tft.print(inorganic);
    else
        tft.print("--");
    tft.println("%");

    // Recyclable
    tft.setCursor(10, 180);
    tft.print("Recyclable: ");
    if (recyclable >= 0)
        tft.print(recyclable);
    else
        tft.print("--");
    tft.println("%");
}

void showReadyScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 100);
    tft.println("READY");
    tft.setCursor(20, 140);
    tft.println("Put trash...");
}

void showProcessingScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 100);
    tft.println("PROCESSING...");
}

void showErrorScreen(String msg)
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);

    tft.setCursor(20, 80);
    tft.println("ERROR");

    tft.setCursor(20, 120);
    tft.println(msg);

    tft.setTextColor(TFT_WHITE);
}

void showSleepScreen()
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(2);
    tft.setCursor(30, 80);
    tft.println("SLEEP MODE");

    tft.setCursor(30, 120);
    tft.println("Waiting...");
}