/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Camera
*/

#include "Camera.hpp"
#include <cmath>

namespace RayTracer {

static double toRadians(double angle)
{
    return angle * M_PI / 180.0;
}

static Math::Vector3D rotateX(const Math::Vector3D &vector, double angle)
{
    const double radians = toRadians(-angle);
    const double cosinus = std::cos(radians);
    const double sinus = std::sin(radians);

    return Math::Vector3D(vector._x, (vector._y * cosinus) - (vector._z * sinus), (vector._y * sinus) + (vector._z * cosinus));
}

static Math::Vector3D rotateY(const Math::Vector3D &vector, double angle)
{
    const double radians = toRadians(-angle);
    const double cosinus = std::cos(radians);
    const double sinus = std::sin(radians);

    return Math::Vector3D((vector._x * cosinus) + (vector._z * sinus), vector._y, (-vector._x * sinus) + (vector._z * cosinus));
}

static Math::Vector3D rotateZ(const Math::Vector3D &vector, double angle)
{
    const double radians = toRadians(-angle);
    const double cosinus = std::cos(radians);
    const double sinus = std::sin(radians);

    return Math::Vector3D((vector._x * cosinus) - (vector._y * sinus), (vector._x * sinus) + (vector._y * cosinus), vector._z);
}

Camera::Camera() : _origin(), _rotation(), _fov(90.0), _width(800), _height(800)
{
}

Camera::Camera(const Math::Point3D &origin, const Math::Vector3D &rotation, double fov, int width, int height) :
    _origin(origin), _rotation(rotation), _fov(fov), _width(width), _height(height)
{
}

int Camera::getWidth() const
{
    return _width;
}

int Camera::getHeight() const
{
    return _height;
}

Ray Camera::ray(double u, double v) const
{
    const double aspect_ratio = static_cast<double>(_width) / _height;
    const double half_height = std::tan(toRadians(_fov) / 2.0);
    const double half_width = aspect_ratio * half_height;
    Math::Vector3D direction((2.0 * u - 1.0) * half_width, (1.0 - 2.0 * v) * half_height, -1.0);

    direction = rotateX(direction, _rotation._x);
    direction = rotateY(direction, _rotation._y);
    direction = rotateZ(direction, _rotation._z);
    return Ray(_origin, direction);
}

void Camera::moveCamera(Math::Vector3D relativeDirection)
{
    Math::Vector3D forward = getForward();
    Math::Vector3D right = getRight();
    
    _origin._x += (forward._x * relativeDirection._z) + (right._x * relativeDirection._x);
    _origin._y += (forward._y * relativeDirection._z) + (right._y * relativeDirection._x);
    _origin._z += (forward._z * relativeDirection._z) + (right._z * relativeDirection._x);
}

void Camera::rotateCamera(Math::Vector3D vector)
{
    _rotation._x -= vector._x;
    _rotation._y -= vector._y;
    _rotation._z -= vector._z;
}

Math::Vector3D Camera::getForward() const
{
    Math::Vector3D forward(0, 0, -1);
    
    forward = rotateX(forward, _rotation._x);
    forward = rotateY(forward, _rotation._y);
    forward = rotateZ(forward, _rotation._z);
    
    return forward;
}

Math::Vector3D Camera::getRight() const
{
    Math::Vector3D right(1, 0, 0);
    
    right = rotateX(right, _rotation._x);
    right = rotateY(right, _rotation._y);
    right = rotateZ(right, _rotation._z);
    
    return right;
}
}
