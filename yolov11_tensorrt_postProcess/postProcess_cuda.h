#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include "common_struct.h"

typedef signed char int8_t;
typedef unsigned int uint32_t;
class GetResultRectYolov11
{
public:
    GetResultRectYolov11();

    ~GetResultRectYolov11();

    int GetConvDetectionResult(DetectRect* OutputRects, int* OutputCount, std::vector<float>& DetectiontRects);


public:

    const int ClassNum = 80;

    int InputW = 640;
    int InputH = 640;

    int MapSize[3][2] = { {80, 80}, {40, 40}, {20, 20} };
    int CoordIndex = 0;

    float NmsThresh = 0.45;
    float ObjectThresh = 0.5;
};

