#pragma once
#include "Base_filter.h"

class Negative : public BaseFilter {
public:
    void Do(Image &image) override;
};
