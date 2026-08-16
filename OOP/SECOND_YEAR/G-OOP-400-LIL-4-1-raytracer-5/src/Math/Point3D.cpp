/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Point3D
*/

#include "Point3D.hpp"

namespace Math {

Point3D::Point3D() : _x(0.0), _y(0.0), _z(0.0)
{
}

Point3D::Point3D(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

Point3D Point3D::operator+(const Vector3D &other) const
{
    return {_x + other._x, _y + other._y, _z + other._z};
}

Point3D Point3D::operator-(const Vector3D &other) const
{
    return {_x - other._x, _y - other._y, _z - other._z};
}

Vector3D Point3D::operator*(const Vector3D &other) const
{
    return {_x * other._x, _y * other._y, _z * other._z};
}

Vector3D Point3D::operator-(const Point3D &other) const
{
    return {_x - other._x, _y - other._y, _z - other._z};
}

}
