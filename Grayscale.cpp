#include "Grayscale.h"

void Grayscale::Do(Image& image) {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            image.SetGreyColor(image.GetColor(j, i), j, i);
        }
    }
}
