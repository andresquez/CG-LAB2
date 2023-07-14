#pragma once
#include <iostream>

struct Color {
    unsigned char r, g, b;

    Color(unsigned char red, unsigned char green, unsigned char blue)
        : r(red), g(green), b(blue) {}

    Color() : r(0), g(0), b(0) {}

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "RGB(" << static_cast<int>(color.r) << ", "
           << static_cast<int>(color.g) << ", " << static_cast<int>(color.b) << ")";
        return os;
    }

    Color operator+(const Color& other) const {
        unsigned char red = r + other.r;
        unsigned char green = g + other.g;
        unsigned char blue = b + other.b;
        return Color(clamp(red), clamp(green), clamp(blue));
    }

    Color operator*(float scalar) const {
        unsigned char red = static_cast<unsigned char>(r * scalar);
        unsigned char green = static_cast<unsigned char>(g * scalar);
        unsigned char blue = static_cast<unsigned char>(b * scalar);
        return Color(clamp(red), clamp(green), clamp(blue));
    }

private:
    unsigned char clamp(unsigned char value) const {
        if (value > 255)
            return 255;
        if (value < 0)
            return 0;
        return value;
    }
};
