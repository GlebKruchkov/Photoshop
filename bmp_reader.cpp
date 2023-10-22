#include "bmp_reader.h"
namespace {
    const int FILE_HEADER_SIZE = 14;
    const int INFORMATION_HEADER_SIZE = 40;
    const double GREY_SCALE_RED = 0.299;
    const double GREY_SCALE_GREEN = 0.587;
    const double GREY_SCALE_BROWN = 0.114;
    const double COLOR_PIXELS = 255.0f;
    const int FILE_SIZE = 5;
    const int ALL_THE_INFORMATION = 10;
    const int IMAGE_WIDTH = 4;
    const int IMAGE_WIDTH_SHIFT_BY_8 = 5;
    const int IMAGE_WIDTH_SHIFT_BY_16 = 6;
    const int IMAGE_WIDTH_SHIFT_BY_24 = 7;
    const int IMAGE_HEIGHT = 8;
    const int IMAGE_HEIGHT_SHIFT_BY_8 = 9;
    const int IMAGE_HEIGHT_SHIFT_BY_16 = 10;
    const int IMAGE_HEIGHT_SHIFT_BY_24 = 11;
    const int PLANES_1 = 12;
    const int PLANES_2 = 13;
    const int BITS_PER_PIXEL_1 = 14;
    const int BITS_PER_PIXEL_2 = 15;
    const int COMPRESSION_1 = 16;
    const int COMPRESSION_2 = 17;
    const int COMPRESSION_3 = 18;
    const int COMPRESSION_4 = 19;
    const int IMAGE_SIZE_1 = 20;
    const int IMAGE_SIZE_2 = 21;
    const int IMAGE_SIZE_3 = 22;
    const int IMAGE_SIZE_4 = 23;
    const int X_PIXELS_PER_METER_1 = 24;
    const int X_PIXELS_PER_METER_2 = 25;
    const int X_PIXELS_PER_METER_3 = 26;
    const int X_PIXELS_PER_METER_4 = 27;
    const int Y_PIXELS_PER_METER_1 = 28;
    const int Y_PIXELS_PER_METER_2 = 29;
    const int Y_PIXELS_PER_METER_3 = 30;
    const int Y_PIXELS_PER_METER_4 = 31;
    const int COLOR_PALETTE_1 = 32;
    const int COLOR_PALETTE_2 = 33;
    const int COLOR_PALETTE_3 = 34;
    const int COLOR_PALETTE_4 = 35;
    const int IMPORTANT_COLORS_1 = 36;
    const int IMPORTANT_COLORS_2 = 37;
    const int IMPORTANT_COLORS_3 = 38;
    const int IMPORTANT_COLORS_4 = 39;
    const int NORMAL_PIXELS_IN_A_BIT = 24;
    const int SHIFT_BY_8 = 8;
    const int SHIFT_BY_16 = 16;
    const int SHIFT_BY_24 = 24;
    const int RESERVED_SPACE_1 = 6;
    const int RESERVED_SPACE_2 = 7;
    const int RESERVED_SPACE_3 = 8;
    const int RESERVED_SPACE_4 = 9;
    const int PIXEL_DATA_OFFSET_1 = 11;
    const int PIXEL_DATA_OFFSET_2 = 12;
    const int PIXEL_DATA_OFFSET_3 = 13;
}  // namespace

Color::Color() : r(0), g(0), b(0) {
}

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {
}

Image::Image(int width, int height)
        : m_width_(width),
          m_height_(height),
          m_colours_(std::vector<std::vector<Color>>(height, std::vector<Color>(width))) {
}

int Image::GetHeight() const {
    return m_height_;
}

int Image::GetWidth() const {
    return m_width_;
}

std::vector<std::vector<Color>> Image::GetMatrix() {
    return m_colours_;
}

void Image::SetMatrix(std::vector<std::vector<Color>> &other) {
    for (int y = 0; y < m_height_; ++y) {
        for (int x = 0; x < m_width_; ++x) {
            m_colours_[y][x] = other[y][x];
        }
    }
}

void Image::SetColor(const Color &color, int x, int y) {
    m_colours_[y][x].r = color.r;
    m_colours_[y][x].g = color.g;
    m_colours_[y][x].b = color.b;
}

void Image::SetNewColor(int x, int y, double change) {
    m_colours_[y][x].r = change;
    m_colours_[y][x].g = change;
    m_colours_[y][x].b = change;
}
void Image::SetNewRedColor(int x, int y, double change) {
    m_colours_[y][x].r = change;
}
void Image::SetNewGreenColor(int x, int y, double change) {
    m_colours_[y][x].g = change;
}
void Image::SetNewBrownColor(int x, int y, double change) {
    m_colours_[y][x].b = change;
}

void Image::SetPlusNewRedColor(int x, int y, double change) {
    m_colours_[y][x].r += change;
}

void Image::SetPlusNewGreenColor(int x, int y, double change) {
    m_colours_[y][x].g += change;
}

void Image::SetPlusNewBrownColor(int x, int y, double change) {
    m_colours_[y][x].b += change;
}

void Image::SetDeriveNewRedColor(int x, int y, double change) {
    m_colours_[y][x].r /= change;
}

void Image::SetDeriveNewGreenColor(int x, int y, double change) {
    m_colours_[y][x].g /= change;
}

void Image::SetDeriveNewBrownColor(int x, int y, double change) {
    m_colours_[y][x].b /= change;
}

Color Image::GetColor(int x, int y) const {
    return m_colours_[y][x];
}

void Image::SetGreyColor(const Color &color, int x, int y) {
    m_colours_[y][x].r = color.r * GREY_SCALE_RED + color.g * GREY_SCALE_GREEN + color.b * GREY_SCALE_BROWN;
    m_colours_[y][x].g = color.r * GREY_SCALE_RED + color.g * GREY_SCALE_GREEN + color.b * GREY_SCALE_BROWN;
    m_colours_[y][x].b = color.r * GREY_SCALE_RED + color.g * GREY_SCALE_GREEN + color.b * GREY_SCALE_BROWN;
}

void Image::SetNegativeColor(const Color &color, int x, int y) {
    m_colours_[y][x].r = 1 - color.r;
    m_colours_[y][x].g = 1 - color.g;
    m_colours_[y][x].b = 1 - color.b;
}

void Image::Read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        throw std::runtime_error("Could not open the file. Incorrect name");
    }

    unsigned char file_header[FILE_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);

    unsigned char information_header[INFORMATION_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(information_header), INFORMATION_HEADER_SIZE);

    m_width_ = information_header[IMAGE_WIDTH] + (information_header[IMAGE_WIDTH_SHIFT_BY_8] << SHIFT_BY_8) +
               (information_header[IMAGE_WIDTH_SHIFT_BY_16] << SHIFT_BY_16) +
               (information_header[IMAGE_WIDTH_SHIFT_BY_24] << SHIFT_BY_24);
    m_height_ = information_header[IMAGE_HEIGHT] + (information_header[IMAGE_HEIGHT_SHIFT_BY_8] << SHIFT_BY_8) +
                (information_header[IMAGE_HEIGHT_SHIFT_BY_16] << SHIFT_BY_16) +
                (information_header[IMAGE_HEIGHT_SHIFT_BY_24] << SHIFT_BY_24);
    m_colours_ = std::vector<std::vector<Color>>(m_height_, std::vector<Color>(m_width_));
    const unsigned int padding_amount = ((4 - (m_width_ * 3) % 4) % 4);

    for (int y = 0; y < m_height_; ++y) {
        for (int x = 0; x < m_width_; ++x) {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);
            m_colours_[y][x].r = color[2] / COLOR_PIXELS;
            m_colours_[y][x].g = color[1] / COLOR_PIXELS;
            m_colours_[y][x].b = color[0] / COLOR_PIXELS;
        }
        f.ignore(padding_amount);
    }
    f.close();
}

void Image::Export(const char *path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    unsigned char bmp_pad[3] = {0, 0, 0};
    const unsigned int padding_amount = ((4 - (m_width_ * 3) % 4) % 4);

    const unsigned int file_size =
            FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + m_width_ * m_height_ * 3 + padding_amount * m_height_;

    unsigned char file_header[FILE_HEADER_SIZE];

    file_header[0] = 'B';
    file_header[1] = 'M';
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::runtime_error("Incorrect expansion of the file");
    }
    file_header[2] = file_size;
    file_header[3] = file_size >> SHIFT_BY_8;
    file_header[4] = file_size >> SHIFT_BY_16;
    file_header[FILE_SIZE] = file_size >> SHIFT_BY_24;
    file_header[RESERVED_SPACE_1] = 0;
    file_header[RESERVED_SPACE_2] = 0;
    file_header[RESERVED_SPACE_3] = 0;
    file_header[RESERVED_SPACE_4] = 0;
    file_header[ALL_THE_INFORMATION] = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE;
    file_header[PIXEL_DATA_OFFSET_1] = 0;
    file_header[PIXEL_DATA_OFFSET_2] = 0;
    file_header[PIXEL_DATA_OFFSET_3] = 0;

    unsigned char information_header[INFORMATION_HEADER_SIZE];

    information_header[0] = INFORMATION_HEADER_SIZE;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;
    information_header[IMAGE_WIDTH] = m_width_;
    information_header[IMAGE_WIDTH_SHIFT_BY_8] = m_width_ >> SHIFT_BY_8;
    information_header[IMAGE_WIDTH_SHIFT_BY_16] = m_width_ >> SHIFT_BY_16;
    information_header[IMAGE_WIDTH_SHIFT_BY_24] = m_width_ >> SHIFT_BY_24;
    information_header[IMAGE_HEIGHT] = m_height_;
    information_header[IMAGE_HEIGHT_SHIFT_BY_8] = m_height_ >> SHIFT_BY_8;
    information_header[IMAGE_HEIGHT_SHIFT_BY_16] = m_height_ >> SHIFT_BY_16;
    information_header[IMAGE_HEIGHT_SHIFT_BY_24] = m_height_ >> SHIFT_BY_24;
    information_header[PLANES_1] = 1;
    information_header[PLANES_2] = 0;
    information_header[BITS_PER_PIXEL_1] = NORMAL_PIXELS_IN_A_BIT;
    if (information_header[BITS_PER_PIXEL_1] != NORMAL_PIXELS_IN_A_BIT) {
        throw std::runtime_error("Too low bits/pixel");
    }
    information_header[BITS_PER_PIXEL_2] = 0;
    information_header[COMPRESSION_1] = 0;
    information_header[COMPRESSION_2] = 0;
    information_header[COMPRESSION_3] = 0;
    information_header[COMPRESSION_4] = 0;
    information_header[IMAGE_SIZE_1] = 0;
    information_header[IMAGE_SIZE_2] = 0;
    information_header[IMAGE_SIZE_3] = 0;
    information_header[IMAGE_SIZE_4] = 0;
    information_header[X_PIXELS_PER_METER_1] = 0;
    information_header[X_PIXELS_PER_METER_2] = 0;
    information_header[X_PIXELS_PER_METER_3] = 0;
    information_header[X_PIXELS_PER_METER_4] = 0;
    information_header[Y_PIXELS_PER_METER_1] = 0;
    information_header[Y_PIXELS_PER_METER_2] = 0;
    information_header[Y_PIXELS_PER_METER_3] = 0;
    information_header[Y_PIXELS_PER_METER_4] = 0;
    information_header[COLOR_PALETTE_1] = 0;
    information_header[COLOR_PALETTE_2] = 0;
    information_header[COLOR_PALETTE_3] = 0;
    information_header[COLOR_PALETTE_4] = 0;
    information_header[IMPORTANT_COLORS_1] = 0;
    information_header[IMPORTANT_COLORS_2] = 0;
    information_header[IMPORTANT_COLORS_3] = 0;
    information_header[IMPORTANT_COLORS_4] = 0;

    f.write(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
    f.write(reinterpret_cast<char *>(information_header), INFORMATION_HEADER_SIZE);

    for (int y = 0; y < m_height_; ++y) {
        for (int x = 0; x < m_width_; ++x) {
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * COLOR_PIXELS);
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * COLOR_PIXELS);
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * COLOR_PIXELS);

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char *>(color), 3);
        }
        f.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
    }
    f.close();
}
