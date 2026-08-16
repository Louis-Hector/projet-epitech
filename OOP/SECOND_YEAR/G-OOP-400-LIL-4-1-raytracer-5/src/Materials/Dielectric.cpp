/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Dielectric
*/

#include "Dielectric.hpp"
#include "MathConstants.hpp"
#include "MathUtils.hpp"
#include <algorithm>
#include <cmath>

namespace RayTracer {

Dielectric::Dielectric() : _color(255, 255, 255), _refraction_index(1.5), _transparency(1.0)
{
}

Dielectric::Dielectric(const Color &color, double refraction_index, double transparency) :
    _color(color), _refraction_index(std::max(refraction_index, 0.001)), _transparency(std::clamp(transparency, 0.0, 1.0))
{
}

Color Dielectric::getAlbedo() const
{
    return _color;
}

bool Dielectric::isDelta() const
{
    return true;
}

bool Dielectric::transmitsLight() const
{
    return _transparency > 0.0;
}

Color Dielectric::getLightTransmission() const
{
    return _color * _transparency;
}

bool Dielectric::scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const
{
    const Math::Vector3D unit_direction = Math::normalize(ray._direction);
    const bool front_face = unit_direction.dot(intersection.surface_normal) < 0.0;
    const Math::Vector3D normal = front_face ? intersection.surface_normal : intersection.surface_normal * -1.0;
    const double eta_ratio = front_face ? (1.0 / _refraction_index) : _refraction_index;
    const double cos_theta = std::fmin((unit_direction * -1.0).dot(normal), 1.0);
    const double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    if (eta_ratio * sin_theta > 1.0)
        return false;
    const Math::Vector3D refracted_direction = Math::refract(unit_direction, normal, eta_ratio);
    scattered = Ray(intersection.position + refracted_direction * EPSILON, refracted_direction);
    transmission = _color * _transparency;
    return true;
}

bool Dielectric::scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    const Math::Vector3D unit_direction = Math::normalize(ray._direction);
    const bool front_face = unit_direction.dot(intersection.surface_normal) < 0.0;
    const Math::Vector3D normal = front_face ? intersection.surface_normal : intersection.surface_normal * -1.0;
    const double eta_ratio = front_face ? (1.0 / _refraction_index) : _refraction_index;
    const double cos_theta = std::fmin((unit_direction * -1.0).dot(normal), 1.0);
    const double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
    const bool cannot_refract = eta_ratio * sin_theta > 1.0;
    Math::Vector3D scatter_direction;

    if (cannot_refract || Math::reflectance(cos_theta, eta_ratio) > Math::randomDouble() || Math::randomDouble() > _transparency) {
        scatter_direction = Math::reflect(unit_direction, normal);
    } else {
        scatter_direction = Math::refract(unit_direction, normal, eta_ratio);
    }
    scattered = Ray(intersection.position + scatter_direction * EPSILON, scatter_direction);
    attenuation = _color;
    return true;
}

}
