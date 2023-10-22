#include "Crop.h"

void Crop::Do(Image& image) {
    if (width_ < 0 || height_ < 0) {
        std::cout << "Use only correct params for the filter : -crop" << std::endl;
        exit(0);
    }
    if (width_ > image.GetWidth()) {
        width_ = image.GetWidth();
    }
    if (height_ > image.GetHeight()) {
        height_ = image.GetHeight();
    }
    Image image_cropped(width_, height_);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            image_cropped.SetColor(image.GetColor(j, image.GetHeight() - i - 1), j, height_ - i - 1);
        }
    }
    image = image_cropped;
}
