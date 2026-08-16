/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace RayTracer {

Sphere::Sphere() : _center(), _radius(0.0), _material(nullptr)
{
}

Sphere::Sphere(Math::Point3D center, double radius, const IMaterial *material) :
    _center(center), _radius(radius), _material(material)
{
}

bool Sphere::hit(const RayTracer::Ray &ray, Intersection &intersection) const
{
    Math::Vector3D oc(ray._origin._x - _center._x,
        ray._origin._y - _center._y, ray._origin._z - _center._z);
    Math::Vector3D direction(ray._direction._x, ray._direction._y, ray._direction._z);

    const double a = direction.dot(direction);
    const double b = 2 * oc.dot(direction);
    const double c = oc.dot(oc) - (_radius * _radius);
    const double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
        return false;
    const double sqrt_discriminant = std::sqrt(discriminant);
    const double first_root = (-b - sqrt_discriminant) / (2 * a);
    const double second_root = (-b + sqrt_discriminant) / (2 * a);
    double t = 0.0;

    if (first_root > 0)
        t = first_root;
    else if (second_root > 0)
        t = second_root;
    else
        return false;
    intersection.distance = t;
    intersection.position = ray._origin + (ray._direction * t);
    intersection.surface_normal = Math::Vector3D(
        (intersection.position._x - _center._x) / _radius,
        (intersection.position._y - _center._y) / _radius,
        (intersection.position._z - _center._z) / _radius);
    intersection.material = _material;
    return true;
}

bool Sphere::boundingBox(AABB &box) const
{
    const Math::Vector3D radius_offset(_radius, _radius, _radius);

    box = AABB(_center - radius_offset, _center + radius_offset);
    return true;
}

}
