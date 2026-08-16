/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

namespace RayTracer {

class Color
{
    public:
        Color();
        Color(double red, double green, double blue);
        ~Color() = default;

        Color operator+(const Color &other) const;
        Color &operator+=(const Color &other);
        Color operator*(double scalar) const;
        Color operator*(const Color &other) const;
        Color clamped(double min_value = 0.0, double max_value = 255.0) const;

        double _r;
        double _g;
        double _b;
};

}

#endif /* !COLOR_HPP_ */
