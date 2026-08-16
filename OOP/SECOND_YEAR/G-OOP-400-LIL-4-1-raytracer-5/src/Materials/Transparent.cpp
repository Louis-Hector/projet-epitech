/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transparent
*/

#include "Transparent.hpp"
#include "MathConstants.hpp"
#include "MathUtils.hpp"

namespace RayTracer {

Color Transparent::getAlbedo() const
{
    return Color(255.0, 255.0, 255.0);
}

bool Transparent::isDelta() const
{
    return true;
}

bool Transparent::transmitsLight() const
{
    return true;
}

Color Transparent::getLightTransmission() const
{
    return Color(255.0, 255.0, 255.0);
}

bool Transparent::scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const
{
    const Math::Vector3D direction = Math::normalize(ray._direction);

    scattered = Ray(intersection.position + direction * EPSILON, direction);
    transmission = Color(255.0, 255.0, 255.0);
    return true;
}

bool Transparent::scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    const Math::Vector3D direction = Math::normalize(ray._direction);

    scattered = Ray(intersection.position + direction * EPSILON, direction);
    attenuation = Color(255.0, 255.0, 255.0);
    return true;
}

}
