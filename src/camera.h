#ifndef CAMERA_SERVICE_H
#define CAMERA_SERVICE_H

#include <Arduino.h>

String captureImage();
typedef struct
{
    String type;
    float confidence;
} WasteInfo;
WasteInfo getWasteInfo(String json);

#endif