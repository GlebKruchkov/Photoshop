#include "Sharpening.h"

void Sharpening::Do(Image& image) {
    std::vector<std::vector<Color>> matrix = image.GetMatrix();
    const int foo = 5;
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            int p_y_min = i - 1;
            int p_x_min = j - 1;
            int p_x_max = j + 1;
            int p_y_max = i + 1;
            if (j == 0) {
                p_x_min = j;
            }
            if (j == image.GetWidth() - 1) {
                p_x_max = j;
            }
            if (i == 0) {
                p_y_min = i;
            }
            if (i == image.GetHeight() - 1) {
                p_y_max = i;
            }
            matrix[i][j].r = Min(
                    1, Max(0, (-image.GetColor(j, p_y_min).r - image.GetColor(j, p_y_max).r - image.GetColor(p_x_min, i).r -
                               image.GetColor(p_x_max, i).r + foo * image.GetColor(j, i).r)));
            matrix[i][j].g = Min(
                    1, Max(0, (-image.GetColor(j, p_y_min).g - image.GetColor(j, p_y_max).g - image.GetColor(p_x_min, i).g -
                               image.GetColor(p_x_max, i).g + foo * image.GetColor(j, i).g)));
            matrix[i][j].b = Min(
                    1, Max(0, (-image.GetColor(j, p_y_min).b - image.GetColor(j, p_y_max).b - image.GetColor(p_x_min, i).b -
                               image.GetColor(p_x_max, i).b + foo * image.GetColor(j, i).b)));
        }
    }
    image.SetMatrix(matrix);
}
