#pragma once
#include <vector>
#include <iostream>
#include "Base_filter.h"
#include "Parser.h"
#include "Crop.h"
#include "Grayscale.h"
#include "Negative.h"
#include "Sharpening.h"
#include "EdgeDetection.h"
#include "Blur.h"
#include "Tape_effect.h"
#include "exception"
#include <memory>
#include "queue"

class Parser {
public:
    Parser(int argc, char** argv) : argc_(argc), argv_(argv) {
    }
    std::queue<std::unique_ptr<BaseFilter>> Parsing();

private:
    int argc_;
    char** argv_;
};
