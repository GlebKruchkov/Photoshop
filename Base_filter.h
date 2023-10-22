#pragma once
#include <cmath>
#include "iostream"
#include <math.h>
#include "bmp_reader.h"

class BaseFilter {
public:
    virtual ~BaseFilter() = default;
    virtual void Do(Image &image) = 0;
};