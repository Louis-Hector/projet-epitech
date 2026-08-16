/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Color
*/

#include "Color.hpp"
#include <algorithm>

namespace RayTracer {

Color::Color() : _r(0.0), _g(0.0), _b(0.0)
{
}

Color::Color(double red, double green, double blue) :
    _r(red), _g(green), _b(blue)
{
}

Color Color::operator+(const Color &other) const
{
    return Color(_r + other._r, _g + other._g, _b + other._b);
}

Color &Color::operator+=(const Color &other)
{
    _r += other._r;
    _g += other._g;
    _b += other._b;
    return *this;
}

Color Color::operator*(double scalar) const
{
    return Color(_r * scalar, _g * scalar, _b * scalar);
}

Color Color::operator*(const Color &other) const
{
    return Color(
        (_r * other._r) / 255.0,
        (_g * other._g) / 255.0,
        (_b * other._b) / 255.0
    );
}

Color Color::clamped(double min_value, double max_value) const
{
    return Color(
        std::clamp(_r, min_value, max_value),
        std::clamp(_g, min_value, max_value),
        std::clamp(_b, min_value, max_value)
    );
}

}
