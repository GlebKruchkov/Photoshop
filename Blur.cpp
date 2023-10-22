#include "Blur.h"

void Blur::Do(Image& image) {
    const int matrix_sigma_size = 3;
    const double pi = 3.14;
    int sigma_size = ceil(sigma_ * matrix_sigma_size);
    int center = sigma_size;
    sigma_size *= 2;
    std::vector<std::vector<double>> sigma_matrix =
            std::vector<std::vector<double>>(sigma_size, std::vector<double>(sigma_size));
    for (int y = 0; y < sigma_size; ++y) {
        sigma_matrix[y][center] = exp(-(((center - y) * (center - y)) / (2 * sigma_ * sigma_)));
    }
    for (int x = 0; x < sigma_size; ++x) {
        sigma_matrix[center][x] = exp(-(((center - x) * (center - x)) / (2 * sigma_ * sigma_)));
    }
    Image vec_new = Image(image.GetWidth(), image.GetHeight());
    for (int y = 0; y < vec_new.GetHeight(); ++y) {
        for (int x = 0; x < vec_new.GetWidth(); ++x) {
            for (int i = 0; i < sigma_size; ++i) {
                int width_tmp = x + i - center;
                if (width_tmp < 0) {
                    width_tmp = 0;
                } else if (width_tmp >= image.GetWidth()) {
                    width_tmp = image.GetWidth() - 1;
                }
                vec_new.SetPlusNewRedColor(x, y, image.GetColor(width_tmp, y).r * sigma_matrix[center][i]);
                vec_new.SetPlusNewGreenColor(x, y, image.GetColor(width_tmp, y).g * sigma_matrix[center][i]);
                vec_new.SetPlusNewBrownColor(x, y, image.GetColor(width_tmp, y).b * sigma_matrix[center][i]);
            }
            const double val = 2 * pi * sigma_ * sigma_;
            vec_new.SetDeriveNewRedColor(x, y, val);
            vec_new.SetDeriveNewGreenColor(x, y, val);
            vec_new.SetDeriveNewBrownColor(x, y, val);
        }
    }
    Image vec_new_result = Image(vec_new.GetWidth(), vec_new.GetHeight());
    for (int y = 0; y < vec_new_result.GetHeight(); ++y) {
        for (int x = 0; x < vec_new_result.GetWidth(); ++x) {
            for (int i = 0; i < sigma_size; ++i) {
                int height_tmp = y + i - center;
                if (height_tmp < 0) {
                    height_tmp = 0;
                } else if (height_tmp >= vec_new.GetHeight()) {
                    height_tmp = vec_new.GetHeight() - 1;
                }
                vec_new_result.SetPlusNewRedColor(x, y, vec_new.GetColor(x, height_tmp).r * sigma_matrix[i][center]);
                vec_new_result.SetPlusNewGreenColor(x, y, vec_new.GetColor(x, height_tmp).g * sigma_matrix[i][center]);
                vec_new_result.SetPlusNewBrownColor(x, y, vec_new.GetColor(x, height_tmp).b * sigma_matrix[i][center]);
            }
        }
    }
    for (int y = 0; y < vec_new_result.GetHeight(); ++y) {
        for (int x = 0; x < vec_new_result.GetWidth(); ++x) {
            image.SetColor(vec_new_result.GetColor(x, y), x, y);
        }
    }
}
