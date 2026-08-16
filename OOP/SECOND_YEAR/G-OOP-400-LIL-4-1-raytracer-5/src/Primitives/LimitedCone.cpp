/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** LimitedCone
*/

#include "LimitedCone.hpp"

namespace RayTracer {

LimitedCone::LimitedCone() : _top(), _angle(0.0), _height(0.0), _material(nullptr)
{
}

LimitedCone::LimitedCone(Math::Point3D top, double angle, double height, const IMaterial *material) : _top(top), _angle(angle), _height(height), _material(material)
{
}

Math::Vector3D LimitedCone::computeNormal(const Math::Vector3D &intersectionPoint) const
{
    double angleRad = _angle * M_PI / 180.0;
    double cosAngle = std::cos(angleRad);
    double k2 = cosAngle * cosAngle;
    Math::Vector3D normal(-k2 * intersectionPoint._x, intersectionPoint._y - k2 * intersectionPoint._y, -k2 * intersectionPoint._z);
    double len = normal.length();
    if (len > EPSILON) {
        normal._x /= len;
        normal._y /= len;
        normal._z /= len;
    }
    return normal;
}

bool LimitedCone::hitBody(const Ray &ray, Intersection &intersection) const
{
    double angleRad = _angle * M_PI / 180.0;
    double cosAngle = std::cos(angleRad);
    double k2 = cosAngle * cosAngle;
    Math::Vector3D oc(ray._origin._x - _top._x, ray._origin._y - _top._y, ray._origin._z - _top._z);
    Math::Vector3D d = ray._direction;
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
        if (intersectionPoint._y > 0)
            continue;
        if (-intersectionPoint._y > _height)
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
    intersection.surface_normal = computeNormal(minDistPoint);
    intersection.material = _material;
    return true;
}

bool LimitedCone::hitBase(const Ray &ray, Intersection &intersection) const
{
    double angleRad = _angle * M_PI / 180.0;
    double radius = std::tan(angleRad) * _height;
    double baseY = _top._y - _height;
    if (std::fabs(ray._direction._y) < EPSILON)
        return false;
    double distance = (baseY - ray._origin._y) / ray._direction._y;
    if (distance <= EPSILON)
        return false;
    Math::Point3D hitPoint = ray._origin + ray._direction * distance;
    double dx = hitPoint._x - _top._x;
    double dz = hitPoint._z - _top._z;
    double dist2 = dx * dx + dz * dz;
    if (dist2 > radius * radius)
        return false;
    intersection.distance = distance;
    intersection.position = hitPoint;
    intersection.surface_normal = Math::Vector3D(0, -1, 0);
    intersection.material = _material;
    return true;
}

bool LimitedCone::hit(const Ray &ray, Intersection &intersection) const
{
    Intersection body;
    Intersection base;
    bool hasBody = hitBody(ray, body);
    bool hasBase = hitBase(ray, base);

    if (!hasBody && !hasBase)
        return false;
    if (hasBody && !hasBase) {
        intersection = body;
    } else if (!hasBody && hasBase) {
        intersection = base;
    } else {
        if (body.distance < base.distance)
            intersection = body;
        else
            intersection = base;
    }
    if (intersection.surface_normal.dot(ray._direction) > 0) {
        intersection.surface_normal._x *= -1;
        intersection.surface_normal._y *= -1;
        intersection.surface_normal._z *= -1;
    }
    return true;
}

bool LimitedCone::boundingBox(AABB &box) const
{
    const double angle_rad = _angle * M_PI / 180.0;
    const double radius = std::tan(angle_rad) * _height;
    const double min_x = _top._x - radius;
    const double max_x = _top._x + radius;
    const double min_y = _top._y - _height;
    const double max_y = _top._y;
    const double min_z = _top._z - radius;
    const double max_z = _top._z + radius;
    box = AABB(Math::Point3D(min_x, min_y, min_z), Math::Point3D(max_x, max_y, max_z));
    return true;
}

}
