/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** SpotLight
*/

#include "SpotLight.hpp"

namespace RayTracer {

SpotLight::SpotLight() : _position(), _direction(0.0, -1.0, 0.0), _angle(30.0), _intensity(1.0), _color(255.0, 255.0, 255.0)
{
}

SpotLight::SpotLight(const Math::Point3D &position, const Math::Vector3D &direction, double angle, double intensity, const Color &color) :
    _position(position), _direction(direction), _angle(angle), _intensity(intensity), _color(color)
{
}

Math::Vector3D SpotLight::getDirectionFrom(const Math::Point3D &point) const
{
    return _position - point;
}

double SpotLight::getDistanceFrom(const Math::Point3D &point) const
{
    return (_position - point).length();
}

double SpotLight::getIntensity() const
{
    return _intensity;
}

Color SpotLight::getColor() const
{
    return _color;
}

Math::Point3D SpotLight::getPosition() const
{
    return _position;
}

Math::Vector3D SpotLight::getAxisDirection() const
{
    return _direction;
}

double SpotLight::getAngle() const
{
    return _angle;
}

}
