#include "EdgeDetection.h"

double Max(double x, double y) {
    if (x >= y) {
        return x;
    }
    return y;
}

double Min(double x, double y) {
    if (x <= y) {
        return x;
    }
    return y;
}

void EdgeDetection::Do(Image& image) {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            image.SetGreyColor(image.GetColor(j, i), j, i);
        }
    }

    Image vec_new = Image(image.GetWidth(), image.GetHeight());

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
            vec_new.SetNewRedColor(j, i,
                                   Min(1, Max(0, (-image.GetColor(j, p_y_min).r - image.GetColor(j, p_y_max).r -
                                                  image.GetColor(p_x_min, i).r - image.GetColor(p_x_max, i).r +
                                                  4 * image.GetColor(j, i).r))));
            vec_new.SetNewGreenColor(j, i,
                                     Min(1, Max(0, (-image.GetColor(j, p_y_min).g - image.GetColor(j, p_y_max).g -
                                                    image.GetColor(p_x_min, i).g - image.GetColor(p_x_max, i).g +
                                                    4 * image.GetColor(j, i).g))));
            vec_new.SetNewBrownColor(j, i,
                                     Min(1, Max(0, (-image.GetColor(j, p_y_min).b - image.GetColor(j, p_y_max).b -
                                                    image.GetColor(p_x_min, i).b - image.GetColor(p_x_max, i).b +
                                                    4 * image.GetColor(j, i).b))));
            if (vec_new.GetMatrix()[i][j].r <= threshold_) {
                vec_new.SetNewRedColor(j, i, 0);
            } else {
                vec_new.SetNewRedColor(j, i, 1);
            }
            if (vec_new.GetMatrix()[i][j].g <= threshold_) {
                vec_new.SetNewGreenColor(j, i, 0);
            } else {
                vec_new.SetNewGreenColor(j, i, 1);
            }
            if (vec_new.GetMatrix()[i][j].b <= threshold_) {
                vec_new.SetNewBrownColor(j, i, 0);
            } else {
                vec_new.SetNewBrownColor(j, i, 1);
            }
        }
    }
    image = vec_new;
}
