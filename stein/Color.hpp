#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <iostream>
#include <cassert>
#include <cmath>

namespace stein {

struct Color {
    float r, g, b, a;

    Color() :
        r(0), g(0), b(0), a(0) {
    }
    Color(float r, float g, float b) :
        r(r), g(g), b(b), a(1) {
    }
    Color(float r, float g, float b, float a) :
        r(r), g(g), b(b), a(a) {
    }
    Color(const Color& c) :
        r(c.r), g(c.g), b(c.b), a(c.a) {
    }

    operator const float*() const {
        return &r;
    }

    static Color BLACK;
    static Color WHITE;
    static Color GRAY;
    static Color RED;
    static Color GREEN;
    static Color BLUE;
};

} // namespace stein

#endif /* COLOR_HPP_ */
