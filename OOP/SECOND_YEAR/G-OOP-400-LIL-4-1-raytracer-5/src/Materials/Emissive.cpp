/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Emissive
*/

#include "Emissive.hpp"
#include <algorithm>

namespace RayTracer {

Emissive::Emissive() : _color(255.0, 245.0, 220.0), _intensity(1.0)
{
}

Emissive::Emissive(const Color &color, double intensity)
    : _color(color)
    , _intensity(std::max(intensity, 0.0))
{
}

Color Emissive::getAlbedo() const
{
    return Color();
}

Color Emissive::emit() const
{
    return _color * _intensity;
}

bool Emissive::isDelta() const
{
    return false;
}

bool Emissive::transmitsLight() const
{
    return false;
}

Color Emissive::getLightTransmission() const
{
    return Color();
}

bool Emissive::scatterShadowRay([[maybe_unused]] const Ray &ray, [[maybe_unused]] const Intersection &intersection,
    [[maybe_unused]] Color &transmission, [[maybe_unused]] Ray &scattered) const
{
    return false;
}

bool Emissive::scatter([[maybe_unused]] const Ray &ray, [[maybe_unused]] const Intersection &intersection,
    [[maybe_unused]] Color &attenuation, [[maybe_unused]] Ray &scattered) const
{
    return false;
}

}
