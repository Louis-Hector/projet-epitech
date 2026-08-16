/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"
#include <limits>

namespace RayTracer {

DirectionalLight::DirectionalLight() : _direction(0.0, -1.0, 0.0), _intensity(1.0), _color(255.0, 255.0, 255.0)
{
}

DirectionalLight::DirectionalLight(const Math::Vector3D &direction, double intensity, const Color &color) :
    _direction(direction), _intensity(intensity), _color(color)
{
}

Math::Vector3D DirectionalLight::getDirectionFrom(__attribute__((unused))const Math::Point3D &point) const
{
    return _direction * -1.0;
}

double DirectionalLight::getDistanceFrom(__attribute__((unused))const Math::Point3D &point) const
{
    return std::numeric_limits<double>::infinity();
}

double DirectionalLight::getIntensity() const
{
    return _intensity;
}

Color DirectionalLight::getColor() const
{
    return _color;
}

}
