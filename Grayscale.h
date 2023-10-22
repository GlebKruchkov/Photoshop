#pragma once
#include "Base_filter.h"

class Grayscale : public BaseFilter {
public:
    void Do(Image &image) override;
};
