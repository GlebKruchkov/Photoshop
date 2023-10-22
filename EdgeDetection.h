#pragma once
#include "Base_filter.h"

class EdgeDetection : public BaseFilter {
public:
    explicit EdgeDetection(double threshold) : threshold_(threshold) {
    }
    void Do(Image &image) override;

private:
    double threshold_;
};

double Max(double x, double y);

double Min(double x, double y);
