#pragma once
#include <vector>
#include <iostream>
#include <fstream>

struct Color {
    double r, g, b;
    Color();
    Color(double r, double g, double b);
};

class Image {
public:
    Image(int width, int height);

    int GetHeight() const;
    int GetWidth() const;
    std::vector<std::vector<Color>> GetMatrix();
    void SetMatrix(std::vector<std::vector<Color>> &other);
    Color GetColor(int x, int y) const;
    void SetNewColor(int x, int y, double change);
    void SetNewRedColor(int x, int y, double change);
    void SetNewGreenColor(int x, int y, double change);
    void SetNewBrownColor(int x, int y, double change);
    void SetPlusNewRedColor(int x, int y, double change);
    void SetPlusNewGreenColor(int x, int y, double change);
    void SetPlusNewBrownColor(int x, int y, double change);
    void SetDeriveNewRedColor(int x, int y, double change);
    void SetDeriveNewGreenColor(int x, int y, double change);
    void SetDeriveNewBrownColor(int x, int y, double change);
    void SetColor(const Color &color, int x, int y);
    void SetGreyColor(const Color &color, int x, int y);
    void SetNegativeColor(const Color &color, int x, int y);

    void Read(const char *path);

    void Export(const char *path) const;

private:
    int m_width_;
    int m_height_;
    std::vector<std::vector<Color>> m_colours_;
};
