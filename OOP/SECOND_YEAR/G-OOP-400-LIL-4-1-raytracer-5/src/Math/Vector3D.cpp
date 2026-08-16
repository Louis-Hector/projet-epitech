/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include "MathConstants.hpp"
#include <cmath>

namespace Math {

Vector3D::Vector3D() : _x(0.0), _y(0.0), _z(0.0)
{
}

Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

double Vector3D::length() const
{
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

double Vector3D::dot(const Vector3D &other) const
{
    return (_x * other._x) + (_y * other._y) + (_z * other._z);
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return {_x + other._x, _y + other._y, _z + other._z};
}

Vector3D Vector3D::operator+=(const Vector3D &other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return {_x - other._x, _y - other._y, _z - other._z};
}

Vector3D Vector3D::operator-=(const Vector3D &other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

Vector3D Vector3D::operator*(const Vector3D &other) const
{
    return {_x * other._x, _y * other._y, _z * other._z};
}

Vector3D Vector3D::operator*=(const Vector3D &other)
{
    _x *= other._x;
    _y *= other._y;
    _z *= other._z;
    return *this;
}

Vector3D Vector3D::operator/(const Vector3D &other) const
{
    return {_x / other._x, _y / other._y, _z / other._z};
}

Vector3D Vector3D::operator/=(const Vector3D &other)
{
    _x /= other._x;
    _y /= other._y;
    _z /= other._z;
    return *this;
}

Vector3D Vector3D::operator*(double value) const
{
    return {_x * value, _y * value, _z * value};
}

Vector3D Vector3D::operator*=(double value)
{
    _x *= value;
    _y *= value;
    _z *= value;
    return *this;
}

Vector3D Vector3D::operator/(double value) const
{
    return {_x / value, _y / value, _z / value};
}

Vector3D Vector3D::operator/=(double value)
{
    _x /= value;
    _y /= value;
    _z /= value;
    return *this;
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
    return Vector3D(_y * other._z - _z * other._y,_z * other._x - _x * other._z, _x * other._y - _y * other._x);
}

/*
 *  Return true if the vector is close to zero in all dimensions.
*/
bool Vector3D::near_zero() const {
    return (std::fabs(_x) < RayTracer::EPSILON) && (std::fabs(_y) < RayTracer::EPSILON) && (std::fabs(_z) < RayTracer::EPSILON);
}

}
