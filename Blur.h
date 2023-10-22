#pragma once
#include "Base_filter.h"

class Blur : public BaseFilter {
public:
    explicit Blur(double sigma) : sigma_(sigma) {
    }
    void Do(Image &image) override;

private:
    double sigma_;
};
