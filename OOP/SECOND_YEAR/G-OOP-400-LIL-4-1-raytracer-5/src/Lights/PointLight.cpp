/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** PointLight
*/

#include "PointLight.hpp"

namespace RayTracer {

PointLight::PointLight() : _position(), _intensity(1.0), _color(255.0, 255.0, 255.0)
{
}

PointLight::PointLight(const Math::Point3D &position, double intensity, const Color &color) :
    _position(position), _intensity(intensity), _color(color)
{
}

Math::Vector3D PointLight::getDirectionFrom(const Math::Point3D &point) const
{
    return _position - point;
}

double PointLight::getDistanceFrom(const Math::Point3D &point) const
{
    return (_position - point).length();
}

double PointLight::getIntensity() const
{
    return _intensity;
}

Color PointLight::getColor() const
{
    return _color;
}

}
