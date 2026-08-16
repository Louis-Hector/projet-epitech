/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Torus
*/

#include "Torus.hpp"
#include "MathUtils.hpp"

namespace RayTracer {

Torus::Torus(/* args */) : _radius_torus(), _radius_tube()
{
}

Torus::Torus(Math::Point3D origin, double radius_torus, double radius_tube, const IMaterial *material) : _origin(origin), _radius_torus(radius_torus), _radius_tube(radius_tube), _material(material)
{
}

bool Torus::hit(const Ray &ray, Intersection &intersection) const
{
    double T_R = _radius_torus;
    double T_r = _radius_tube;
    Math::Vector3D new_point = ray._origin - _origin;
    double doto = new_point._x * new_point._x + new_point._y * new_point._y + new_point._z * new_point._z;
    double dotd = ray._direction._x * ray._direction._x + ray._direction._y * ray._direction._y + ray._direction._z * ray._direction._z;
    double dotod = new_point._x * ray._direction._x + new_point._y * ray._direction._y + new_point._z * ray._direction._z;
    double first_part = doto + (T_R * T_R) - (T_r * T_r);
    double A = dotd * dotd;
    double B = 4.0 * dotd * dotod;
    double C = 2.0 * dotd * first_part  + 4.0 * dotod * dotod - 4.0 * T_R * T_R * (ray._direction._x * ray._direction._x + ray._direction._y * ray._direction._y);
    double D = 4.0 * dotod * first_part - 8.0 * T_R * T_R * (new_point._x * ray._direction._x + new_point._y * ray._direction._y);
    double E = first_part * first_part - 4.0 * T_R * T_R * (new_point._x * new_point._x + new_point._y * new_point._y);
    std::vector<double> roots = Math::resolve_exp4(A, B, C, D, E);
    double min_root = 1e60;
    for (double root : roots)
        if (root > 1e-6 && root < min_root)
            min_root = root;
    if (min_root == 1e60)
        return false;
    Math::Vector3D p_l= new_point + ray._direction * min_root;
    Math::Point3D p_hit(p_l._x + _origin._x, p_l._y + _origin._y, p_l._z + _origin._z);
    double length = std::sqrt(p_l._x * p_l._x + p_l._y * p_l._y);
    Math::Vector3D center_circle;
    if (length > 0)
        center_circle = Math::Vector3D((T_R * p_l._x / length), (T_R * p_l._y / length), 0.0);
    else
        center_circle = Math::Vector3D(0, 0, 0);
    Math::Vector3D normal = p_l - center_circle;
    double len = normal.length();
    if (len > EPSILON) {
        normal._x /= len;
        normal._y /= len;
        normal._z /= len;
    }
    intersection.distance = min_root;
    intersection.material = _material;
    intersection.position = p_hit;
    intersection.surface_normal = normal;
    return true;
}

bool Torus::boundingBox(AABB &box) const
{
    const double radial_extent = _radius_torus + _radius_tube;

    box = AABB(Math::Point3D(_origin._x - radial_extent, _origin._y - radial_extent, _origin._z - _radius_tube),
        Math::Point3D(_origin._x + radial_extent, _origin._y + radial_extent, _origin._z + _radius_tube));
    return true;
}

}
