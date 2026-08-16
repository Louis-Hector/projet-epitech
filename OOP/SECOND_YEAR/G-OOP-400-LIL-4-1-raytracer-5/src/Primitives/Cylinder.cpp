/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

namespace RayTracer {

Cylinder::Cylinder() : _center(), _radius(0.0), _material(nullptr)
{
}

Cylinder::Cylinder(Math::Point3D center, Math::Vector3D rotation, double radius, const IMaterial *material) :
    _center(center), _rotation(rotation), _radius(radius), _material(material)
{
}

// bool Cylinder::hit(const RayTracer::Ray &ray, Intersection &intersection) const
// {
//     if (_radius <= 0.0)
//         return false;
//     const double offset_x = ray._origin._x - _center._x;
//     const double offset_z = ray._origin._z - _center._z;
//     const double a = (ray._direction._x * ray._direction._x) + (ray._direction._z * ray._direction._z);
//     const double b = (2.0 * offset_x * ray._direction._x) + (2.0 * offset_z * ray._direction._z);
//     const double c = (offset_x * offset_x) + (offset_z * offset_z) - (_radius * _radius);
//     const double discriminant = (b * b) - (4 * a * c);

//     if (a <= EPSILON || discriminant < 0)
//         return false;
//     const double sqrt_discriminant = std::sqrt(discriminant);
//     const double first_root = (-b - sqrt_discriminant) / (2 * a);
//     const double second_root = (-b + sqrt_discriminant) / (2 * a);
//     double t = 0.0;

//     if (first_root > 0)
//         t = first_root;
//     else if (second_root > 0)
//         t = second_root;
//     else
//         return false;
//     intersection.distance = t;
//     intersection.position = ray._origin + (ray._direction * t);
//     intersection.surface_normal = Math::Vector3D(
//         (intersection.position._x - _center._x) / _radius,
//         0.0,
//         (intersection.position._z - _center._z) / _radius);
//     intersection.material = _material;
//     return true;
// }

bool Cylinder::hit(const RayTracer::Ray &ray, Intersection &intersection) const
{
    if (_radius <= 0.0)
        return false;
    Math::Point3D origin(ray._origin._x - _center._x, ray._origin._y - _center._y,ray._origin._z - _center._z);
    Math::Point3D direction(ray._direction._x, ray._direction._y, ray._direction._z);
    change_rotate(origin, -_rotation._x, -_rotation._y, -_rotation._z);
    change_rotate(direction, -_rotation._x, -_rotation._y, -_rotation._z);
    const double a = (direction._x * direction._x) + (direction._z * direction._z);
    const double b = (2.0 * origin._x * direction._x) + (2.0 * origin._z * direction._z);
    const double c = (origin._x * origin._x) + (origin._z * origin._z) - (_radius * _radius);
    const double discriminant = (b * b) - (4.0 * a * c);
    if (a <= EPSILON || discriminant < 0.0)
        return false;
    const double sqrt_discriminant = std::sqrt(discriminant);
    const double first_root = (-b - sqrt_discriminant) / (2.0 * a);
    const double second_root = (-b + sqrt_discriminant) / (2.0 * a);
    double t = 0.0;
    if (first_root > EPSILON)
        t = first_root;
    else if (second_root > EPSILON)
        t = second_root;
    else
        return false;
    intersection.distance = t;
    intersection.position = ray._origin + (ray._direction * t);
    Math::Point3D normal((origin._x + direction._x * t) / _radius, 0.0, (origin._z + direction._z * t) / _radius);
    change_rotate(normal, _rotation._x, _rotation._y, _rotation._z);
    intersection.surface_normal = Math::Vector3D(normal._x, normal._y, normal._z);
    intersection.material = _material;
    return true;
}

bool Cylinder::boundingBox([[maybe_unused]] AABB &box) const
{
    return false;
}

}
