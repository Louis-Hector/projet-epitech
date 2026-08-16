/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Plane
*/

#include "Plane.hpp"
#include <cmath>

namespace RayTracer {

Plane::Plane() : _point(), _normal(0.0, 1.0, 0.0), _material(nullptr)
{
}

Plane::Plane(Math::Point3D point, Math::Vector3D rotation, Math::Vector3D normal, const IMaterial *material) :
    _point(point), _rotation(rotation), _normal(normal), _material(material)
{
}

bool Plane::hit(const RayTracer::Ray &ray, Intersection &intersection) const
{
    const double normal_length = _normal.length();

    if (normal_length == 0.0)
        return false;
    Math::Point3D origin = ray._origin;
    Math::Vector3D direction = ray._direction;
    change_rotate(origin, -_rotation._x, -_rotation._y, -_rotation._z);
    change_rotate(direction, -_rotation._x, -_rotation._y, -_rotation._z);
    const Math::Vector3D unit_normal = _normal / normal_length;
    const double denominator = unit_normal.dot(direction);
    if (std::fabs(denominator) < EPSILON)
        return false;
    const Math::Vector3D point_offset(_point._x - origin._x, _point._y - origin._y, _point._z - origin._z);
    const double distance = point_offset.dot(unit_normal) / denominator;
    if (distance <= 0.0)
        return false;
    intersection.distance = distance;
    intersection.position = origin + (direction * distance);
    intersection.surface_normal = unit_normal;
    Math::Vector3D normal = unit_normal;
    change_rotate(normal, _rotation._x, _rotation._y, _rotation._z);
    double len = normal.length();
    if (len > EPSILON) {
        normal._x /= len;
        normal._y /= len;
        normal._z /= len;
    }
    intersection.surface_normal = normal;
    intersection.material = _material;
    return true;
}

bool Plane::boundingBox([[maybe_unused]] AABB &box) const
{
    return false;
}

}
