/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** LimitedCylinder
*/

#include "LimitedCylinder.hpp"

namespace RayTracer {

LimitedCylinder::LimitedCylinder() : _center(), _height(0.0), _radius(0.0), _material(nullptr)
{
}

LimitedCylinder::LimitedCylinder(Math::Point3D center, double height, double radius, const IMaterial *material) :
    _center(center), _height(height), _radius(radius), _material(material)
{
}

bool LimitedCylinder::inBounds(const RayTracer::Ray &ray, double t) const
{
    const double hit_y = ray._origin._y + (ray._direction._y * t);
    const double min_y = _center._y - (_height / 2.0);
    const double max_y = _center._y + (_height / 2.0);

    if (hit_y < min_y || hit_y > max_y)
        return false;
    return true;
}

bool LimitedCylinder::intersectCap(const RayTracer::Ray &ray, double cap_y,
    double normal_y, Intersection &intersection) const
{
    if (std::fabs(ray._direction._y) <= EPSILON)
        return false;
    const double t = (cap_y - ray._origin._y) / ray._direction._y;

    if (t <= 0.0)
        return false;
    const Math::Point3D position = ray._origin + (ray._direction * t);
    const double offset_x = position._x - _center._x;
    const double offset_z = position._z - _center._z;

    if ((offset_x * offset_x) + (offset_z * offset_z) > (_radius * _radius))
        return false;
    intersection.distance = t;
    intersection.position = position;
    intersection.surface_normal = Math::Vector3D(0.0, normal_y, 0.0);
    intersection.material = _material;
    return true;
}

bool LimitedCylinder::intersectSide(const RayTracer::Ray &ray,  Intersection &intersection) const
{
    const double offset_x = ray._origin._x - _center._x;
    const double offset_z = ray._origin._z - _center._z;
    const double a = (ray._direction._x * ray._direction._x) +
        (ray._direction._z * ray._direction._z);
    const double b = (2.0 * offset_x * ray._direction._x) +
        (2.0 * offset_z * ray._direction._z);
    const double c = (offset_x * offset_x) + (offset_z * offset_z) - (_radius * _radius);
    const double discriminant = (b * b) - (4 * a * c);

    if (a <= EPSILON || discriminant < 0.0)
        return false;
    const double sqrt_discriminant = std::sqrt(discriminant);
    const double first_root = (-b - sqrt_discriminant) / (2 * a);
    const double second_root = (-b + sqrt_discriminant) / (2 * a);
    double t = 0.0;

    if (first_root > 0.0 && inBounds(ray, first_root))
        t = first_root;
    else if (second_root > 0.0 && inBounds(ray, second_root))
        t = second_root;
    if (t <= 0.0)
        return false;
    intersection.distance = t;
    intersection.position = ray._origin + (ray._direction * t);
    intersection.surface_normal = Math::Vector3D(
        (intersection.position._x - _center._x) / _radius,
        0.0,
        (intersection.position._z - _center._z) / _radius);
    intersection.material = _material;
    return true;
}

bool LimitedCylinder::hit(const RayTracer::Ray &ray, Intersection &intersection) const
{
    if (_radius <= 0.0 || _height <= 0.0)
        return false;
    bool found_intersection = intersectSide(ray, intersection);
    const double half_height = _height / 2.0;
    Intersection top_cap_intersection;
    Intersection bottom_cap_intersection;

    if (intersectCap(ray, _center._y + half_height, 1.0, top_cap_intersection) &&
        (!found_intersection || top_cap_intersection.distance < intersection.distance)) {
        intersection = top_cap_intersection;
        found_intersection = true;
    }
    if (intersectCap(ray, _center._y - half_height, -1.0, bottom_cap_intersection) &&
        (!found_intersection || bottom_cap_intersection.distance < intersection.distance)) {
        intersection = bottom_cap_intersection;
        found_intersection = true;
    }
    return found_intersection;
}

bool LimitedCylinder::boundingBox(AABB &box) const
{
    const Math::Point3D minimum(_center._x - _radius, _center._y - (_height / 2.0), _center._z - _radius);
    const Math::Point3D maximum(_center._x + _radius, _center._y + (_height / 2.0), _center._z + _radius);
    box = AABB(minimum, maximum);
    return true;
}

}
