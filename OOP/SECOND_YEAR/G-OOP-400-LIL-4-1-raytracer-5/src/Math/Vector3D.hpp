/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

namespace Math {

class Vector3D
{
    public:
        double _x;
        double _y;
        double _z;
        Vector3D();
        Vector3D(double x, double y, double z);
        ~Vector3D() = default;
        double length() const;
        double dot(const Vector3D &other) const;
        Vector3D cross(const Vector3D &other) const;
        bool near_zero() const;
        Vector3D operator+(const Vector3D &other) const;
        Vector3D operator+=(const Vector3D &other);
        Vector3D operator-(const Vector3D &other) const;
        Vector3D operator-=(const Vector3D &other);
        Vector3D operator*(const Vector3D &other) const;
        Vector3D operator*=(const Vector3D &other);
        Vector3D operator/(const Vector3D &other) const;
        Vector3D operator/=(const Vector3D &other);
        Vector3D operator*(double value) const;
        Vector3D operator*=(double value);
        Vector3D operator/(double value) const;
        Vector3D operator/=(double value);
};

}

#endif /* !VECTOR3D_HPP_ */
