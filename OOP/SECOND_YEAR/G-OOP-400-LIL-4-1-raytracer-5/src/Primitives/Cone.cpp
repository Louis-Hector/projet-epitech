/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Cone
*/

#include "Cone.hpp"

namespace RayTracer {

Cone::Cone() : _top(), _angle(0.0), _material(nullptr)
{
}

Cone::Cone(Math::Point3D top, Math::Vector3D rotation, double angle, const IMaterial *material) : _top(top), _rotation(rotation), _angle(angle), _material(material)
{
}

Math::Vector3D Cone::computeNormal(const Math::Vector3D &intersectionPoint) const
{
    Math::Vector3D new_point(intersectionPoint._x, intersectionPoint._y, intersectionPoint._z);
    double angleRad = _angle * M_PI / 180.0;
    double cosAngle = std::cos(angleRad);
    double k2 = cosAngle * cosAngle;
    Math::Vector3D normal(-k2 * new_point._x, new_point._y - k2 * new_point._y, -k2 * new_point._z);
    double len = normal.length();
    if (len > EPSILON) {
        normal._x /= len;
        normal._y /= len;
        normal._z /= len;
    }
    return normal;
}

bool Cone::hit(const Ray &ray, Intersection &intersection) const
{
    double angleRad = _angle * M_PI / 180.0;
    double cosAngle = std::cos(angleRad);
    double k2 = cosAngle * cosAngle;
    Math::Vector3D oc(ray._origin._x - _top._x, ray._origin._y - _top._y, ray._origin._z - _top._z);
    Math::Vector3D d = ray._direction;
    change_rotate(oc, -_rotation._x, -_rotation._y, -_rotation._z);
    change_rotate(d, -_rotation._x, -_rotation._y, -_rotation._z);
    double a = d._y * d._y - k2 * d.dot(d);
    double b = 2.0 * (oc._y * d._y - k2 * oc.dot(d));
    double c = oc._y * oc._y - k2 * oc.dot(oc);
    if (std::fabs(a) < EPSILON)
        return false;
    double delta = b * b - 4.0 * a * c;
    if (delta < 0)
        return false;
    double sqrtDelta = std::sqrt(delta);
    double solution1 = (-b - sqrtDelta) / (2.0 * a);
    double solution2 = (-b + sqrtDelta) / (2.0 * a);
    double min_dist = std::numeric_limits<double>::max();
    Math::Vector3D minDistPoint;
    double roots[2] = {solution1, solution2};
    for (double solution : roots) {
        if (solution <= EPSILON)
            continue;
        Math::Vector3D intersectionPoint = oc + d * solution;
        if (intersectionPoint._y > _top._y)
            continue;
        if (solution < min_dist) {
            min_dist = solution;
            minDistPoint = intersectionPoint;
        }
    }
    if (min_dist == std::numeric_limits<double>::max())
        return false;
    intersection.distance = min_dist;
    intersection.position = ray._origin + ray._direction * min_dist;
    Math::Vector3D normal = computeNormal(minDistPoint);
    change_rotate(normal, _rotation._x, _rotation._y, _rotation._z);
    double len = normal.length();
    if (len > EPSILON) {
        normal._x /= len;
        normal._y /= len;
        normal._z /= len;
    }
    intersection.surface_normal = normal;
    if (intersection.surface_normal.dot(ray._direction) > 0) {
        intersection.surface_normal._x *= -1;
        intersection.surface_normal._y *= -1;
        intersection.surface_normal._z *= -1;
    }
    intersection.material = _material;
    return true;
}

bool Cone::boundingBox([[maybe_unused]] AABB &box) const
{
    return false;
}

}
