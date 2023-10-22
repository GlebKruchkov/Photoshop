#pragma once
#include "Base_filter.h"
#include "EdgeDetection.h"

class TapeEffect : public BaseFilter {
public:
    void Do(Image &image) override;
};