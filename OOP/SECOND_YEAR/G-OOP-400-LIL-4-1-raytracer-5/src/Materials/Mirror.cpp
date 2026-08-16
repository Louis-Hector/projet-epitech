/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Mirror
*/

#include "Mirror.hpp"
#include "MathUtils.hpp"
#include "MathConstants.hpp"

namespace RayTracer {

Mirror::Mirror() : _color(235, 235, 245)
{
}

Mirror::Mirror(const Color &color) : _color(color)
{
}

Color Mirror::getAlbedo() const
{
    return _color;
}

bool Mirror::isDelta() const
{
    return true;
}

bool Mirror::transmitsLight() const
{
    return false;
}

Color Mirror::getLightTransmission() const
{
    return Color();
}

bool Mirror::scatterShadowRay([[maybe_unused]] const Ray &ray, [[maybe_unused]] const Intersection &intersection,
    [[maybe_unused]] Color &transmission, [[maybe_unused]] Ray &scattered) const
{
    return false;
}

bool Mirror::scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    const Math::Vector3D reflected = Math::reflect(Math::normalize(ray._direction), intersection.surface_normal);

    scattered = Ray(intersection.position + intersection.surface_normal * EPSILON, reflected);
    attenuation = _color;
    return true;
}

}
