#pragma once

#include <stdio.h>
#include "common_struct.h"
#include <driver_types.h>

void GetNmsBeforeBoxes(float* SrcInput, int AnchorCount, int ClassNum, float ObjectThresh, int NMSBeforeMaxNum, DetectRect* OutputRects, int* OutputCount, cudaStream_t Stream);