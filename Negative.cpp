#include "Negative.h"

void Negative::Do(Image& image) {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            image.SetNegativeColor(image.GetColor(j, i), j, i);
        }
    }
}
