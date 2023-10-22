#include "Tape_effect.h"
namespace {
    const int MAX_COLOR_VALUE = 255;
    const double CONTRAST_EFFECT1 = 259.0;
    const double CONTRAST_EFFECT2 = 255.0;
    const double CONTRAST_EFFECT3 = 128;
    const double NOISE_FREQUENCY = 0.3;
    const double CONTRAST = -60.0;
    const double SIGMA = 3;
    const double PI = M_PI;
    const int MATRIX_SIGMA_SIZE = 3;
}  // namespace

double Truncate(double value) {
    if (value < 0) {
        return 0;
    }
    if (value > MAX_COLOR_VALUE) {
        return MAX_COLOR_VALUE;
    }
    return value;
}

void TapeEffect::Do(Image &image) {
    int sigma_size = ceil(SIGMA * MATRIX_SIGMA_SIZE);
    int center = sigma_size;
    sigma_size *= 2;
    std::vector<std::vector<double>> sigma_matrix =
            std::vector<std::vector<double>>(sigma_size, std::vector<double>(sigma_size));
    for (int y = 0; y < sigma_size; ++y) {
        sigma_matrix[y][center] = exp(-((std::pow((center - y), 2)) / (2 * std::pow(SIGMA, 2))));
    }
    for (int x = 0; x < sigma_size; ++x) {
        sigma_matrix[center][x] = exp(-((std::pow((center - x), 2)) / (2 * std::pow(SIGMA, 2))));
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
            const double val = 2 * PI * std::pow(SIGMA, 2);
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
    image = vec_new_result;

    std::vector<std::vector<Color>> matrix = image.GetMatrix();
    double factor = static_cast<double>((CONTRAST_EFFECT1 * (CONTRAST + CONTRAST_EFFECT2)) /
                                        (CONTRAST_EFFECT2 * (CONTRAST_EFFECT1 - CONTRAST)));
    int cnt_noise_pixels = static_cast<int>(image.GetWidth() * image.GetHeight() * NOISE_FREQUENCY);
    for (int i = 0; i < cnt_noise_pixels; i++) {
        int x = rand() % static_cast<int>(image.GetWidth());
        int y = rand() % static_cast<int>(image.GetHeight());
        matrix[y][x].r = Truncate(factor * (image.GetColor(x, y).r - CONTRAST_EFFECT3) + CONTRAST_EFFECT3);
        matrix[y][x].g = Truncate(factor * (image.GetColor(x, y).g - CONTRAST_EFFECT3) + CONTRAST_EFFECT3);
        matrix[y][x].g = Truncate(factor * (image.GetColor(x, y).b - CONTRAST_EFFECT3) + CONTRAST_EFFECT3);
    }
    image.SetMatrix(matrix);
}
