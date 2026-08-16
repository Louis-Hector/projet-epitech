/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Mobius
*/

#include "Mobius.hpp"
#include "MathUtils.hpp"

namespace RayTracer {

Mobius::Mobius() : _origin(), _radius(1.0), _material(nullptr)
{
}

Mobius::Mobius(Math::Point3D origin, double radius, const IMaterial *material) : _origin(origin), _radius(radius), _material(material)
{
}

void Mobius::calculateEquation(const Math::Vector3D &origin, const Math::Vector3D &direction, double &a, double &b, double &c, double &d) const
{
    a = direction._x * direction._x * direction._y + direction._y * direction._z * direction._z + direction._y * direction._y * direction._y - 2.0 * direction._x * direction._x * direction._z - 2.0 * direction._y * direction._y * direction._z;
    b = 2.0 * origin._x * direction._x * direction._y + direction._x * direction._x * origin._y + 2.0 * direction._y * origin._z * direction._z + origin._y * direction._z * direction._z + 3.0 * origin._y * direction._y * direction._y - 2.0 * direction._x * direction._z - 2.0 * (2.0 * origin._x * direction._x * direction._z + direction._x * direction._x * origin._z) - 2.0 * (2.0 * origin._y * direction._y * direction._z + direction._y * direction._y * origin._z);
    c = origin._x * origin._x * direction._y + 2.0 * origin._x * direction._x * origin._y + direction._y * origin._z * origin._z + 2.0 * origin._y * origin._z * direction._z + 3.0 * origin._y * origin._y * direction._y - direction._y - 2.0 * (origin._x * direction._z + direction._x * origin._z) - 2.0 * (origin._x * origin._x * direction._z + 2.0 * origin._x * direction._x * origin._z) - 2.0 * (origin._y * origin._y * direction._z + 2.0 * origin._y * direction._y * origin._z);
    d = origin._x * origin._x * origin._y + origin._y * origin._z * origin._z + origin._y * origin._y * origin._y - origin._y - 2.0 * origin._x * origin._z - 2.0 * origin._x * origin._x * origin._z - 2.0 * origin._y * origin._y * origin._z;
}

bool Mobius::isInMobius(const Math::Vector3D &point) const
{
    double angle = std::atan2(point._y, point._x);

    if (angle < 0.0)
        angle += 2.0 * M_PI;
    double cos_v = std::cos(angle);
    double sin_v = std::sin(angle);
    double cos_half = std::cos(angle / 2.0);
    double sin_half = std::sin(angle / 2.0);
    Math::Vector3D center(cos_v, sin_v, 0.0);
    Math::Vector3D direction(0.5 * cos_half * cos_v, 0.5 * cos_half * sin_v, 0.5 * sin_half);
    Math::Vector3D diff = point - center;
    double absolute_direction = direction.dot(direction);
    if (absolute_direction <= EPSILON)
        return false;
    double pos = diff.dot(direction) / absolute_direction;
    if (pos < -1.0 || pos > 1.0)
        return false;
    Math::Vector3D point_out = point - (center + direction * pos);
    double absolute_point_out = point_out.dot(point_out);
    if (absolute_point_out <= EPSILON)
        return true;
    return false;
}

Math::Vector3D Mobius::calculateNormal(const Math::Vector3D &point) const
{
    double x = point._x;
    double y = point._y;
    double z = point._z;
    Math::Vector3D normal(2.0 * x * y - 2.0 * z - 4.0 * x * z, x * x + z * z + 3.0 * y * y - 1.0 - 4.0 * y * z, 2.0 * y * z - 2.0 * x - 2.0 * x * x - 2.0 * y * y);
    double len = normal.length();
    if (len > EPSILON) {
        normal._x /= len;
        normal._y /= len;
        normal._z /= len;
    }
    return normal;
}

bool Mobius::hit(const Ray &ray, Intersection &intersection) const
{
    if (_radius <= EPSILON)
        return false;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double d = 0.0;
    Math::Vector3D origin((ray._origin._x - _origin._x) / _radius, (ray._origin._z - _origin._z) / _radius, (ray._origin._y - _origin._y) / _radius);
    Math::Vector3D direction(ray._direction._x / _radius, ray._direction._z / _radius, ray._direction._y / _radius);
    calculateEquation(origin, direction, a, b, c, d);
    std::vector<double> solutions = Math::resolve_exp3(a, b, c, d);
    double min_dist = std::numeric_limits<double>::max();
    Math::Vector3D good_intersection_point;
    for (double solution : solutions) {
        if (solution <= EPSILON)
            continue;
        Math::Vector3D intersection_point = origin + direction * solution;
        if (!isInMobius(intersection_point))
            continue;
        if (solution < min_dist) {
            min_dist = solution;
            good_intersection_point = intersection_point;
        }
    }
    if (min_dist == std::numeric_limits<double>::max())
        return false;
    Math::Vector3D normal = calculateNormal(good_intersection_point);
    if (normal.dot(ray._direction) > 0.0) {
        normal._x *= -1.0;
        normal._y *= -1.0;
        normal._z *= -1.0;
    }
    intersection.distance = min_dist;
    intersection.position = ray._origin + ray._direction * min_dist;
    intersection.surface_normal = normal;
    intersection.material = _material;
    return true;
}

bool Mobius::boundingBox(AABB &box) const
{
    const double extent_xy = _radius * 1.6;
    const double extent_z = _radius * 0.6;

    box = AABB(Math::Point3D(_origin._x - extent_xy, _origin._y - extent_xy, _origin._z - extent_z),
        Math::Point3D(_origin._x + extent_xy, _origin._y + extent_xy, _origin._z + extent_z));
    return true;
}

}
