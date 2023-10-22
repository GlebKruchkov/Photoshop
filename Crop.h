#pragma once
#include "Base_filter.h"

class Crop : public BaseFilter {
public:
    Crop(int x, int y) : width_(x), height_(y) {
    }
    void Do(Image &image) override;

private:
    int width_;
    int height_;
};
