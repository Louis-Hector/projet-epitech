/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Lambertian
*/

#include "Lambertian.hpp"
#include "MathConstants.hpp"
#include "MathUtils.hpp"

namespace RayTracer {

Lambertian::Lambertian() : _color()
{
}

Lambertian::Lambertian(const Color &color) : _color(color)
{
}

Color Lambertian::getAlbedo() const
{
    return _color;
}

bool Lambertian::isDelta() const
{
    return false;
}

bool Lambertian::transmitsLight() const
{
    return false;
}

Color Lambertian::getLightTransmission() const
{
    return Color();
}

bool Lambertian::scatterShadowRay([[maybe_unused]] const Ray &ray, [[maybe_unused]] const Intersection &intersection,
    [[maybe_unused]] Color &transmission, [[maybe_unused]] Ray &scattered) const
{
    return false;
}

bool Lambertian::scatter([[maybe_unused]] const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    Math::Vector3D scatter_direction = intersection.surface_normal + Math::randomUnitVector();

    if (scatter_direction.near_zero())
        scatter_direction = intersection.surface_normal;
    scattered = Ray(intersection.position + intersection.surface_normal * EPSILON, scatter_direction);
    attenuation = _color;
    return true;
}

}
