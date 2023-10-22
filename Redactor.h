#pragma once
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

class Redactor {
public:
    Redactor(std::queue<std::unique_ptr<BaseFilter>> filters_new, char* output_path, Image image)
            : filters_new_(std::move(filters_new)), output_path_(output_path), image_(image) {
    }
    void RedactFile();

private:
    std::queue<std::unique_ptr<BaseFilter>> filters_new_;
    char* output_path_;
    Image image_;
};
