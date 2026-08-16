/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include "Vector3D.hpp"

namespace Math {

class Point3D
{
    public:
        double _x;
        double _y;
        double _z;
        Point3D();
        Point3D(double x, double y, double z);
        ~Point3D() = default;
        Point3D operator+(const Vector3D &other) const;
        Point3D operator-(const Vector3D &other) const;
        Vector3D operator*(const Vector3D &other) const;
        Vector3D operator-(const Point3D &other) const;
};

}


#endif /* !POINT3D_HPP_ */
