/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Metal
*/

#include "Metal.hpp"
#include "MathUtils.hpp"
#include "MathConstants.hpp"
#include <algorithm>

namespace RayTracer {

Metal::Metal() : _color(200, 200, 210), _fuzz(0.0)
{
}

Metal::Metal(const Color &color) : _color(color), _fuzz(0.0)
{
}

Metal::Metal(const Color &color, double fuzz) : _color(color), _fuzz(std::clamp(fuzz, 0.0, 1.0))
{
}

Color Metal::getAlbedo() const
{
    return _color;
}

bool Metal::isDelta() const
{
    return true;
}

bool Metal::transmitsLight() const
{
    return false;
}

Color Metal::getLightTransmission() const
{
    return Color();
}

bool Metal::scatterShadowRay([[maybe_unused]] const Ray &ray, [[maybe_unused]] const Intersection &intersection,
    [[maybe_unused]] Color &transmission, [[maybe_unused]] Ray &scattered) const
{
    return false;
}

bool Metal::scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    const Math::Vector3D reflected = Math::reflect(Math::normalize(ray._direction), intersection.surface_normal);
    const Math::Vector3D scatter_direction = Math::normalize(reflected + Math::randomUnitVector() * _fuzz);

    scattered = Ray(intersection.position + intersection.surface_normal * EPSILON, scatter_direction);
    attenuation = _color;
    return scatter_direction.dot(intersection.surface_normal) > 0.0;
}

}
