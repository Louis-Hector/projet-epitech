/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Triangle
*/

#include "Triangle.hpp"
#include <algorithm>

namespace RayTracer {

Triangle::Triangle() : _v0(), _v1(), _v2(), _material(nullptr)
{
}

Triangle::Triangle(Math::Point3D A, Math::Point3D B, Math::Point3D C, const IMaterial *material) :
    _v0(A), _v1(B), _v2(C), _material(material)
{
}

bool Triangle::hit(const Ray &ray, Intersection &intersection) const
{
    Math::Vector3D c1 = _v1 - _v0;
    Math::Vector3D c2 = _v2 - _v0;
    Math::Vector3D vecteur_h = ray._direction.cross(c2);
    double radius = c1.dot(vecteur_h);

    if (radius > -EPSILON && radius < EPSILON)
        return false;
    double force = 1.0 / radius;
    Math::Vector3D o_radius = ray._origin - _v0;
    double coord_bary_u = force * (o_radius.dot(vecteur_h));
    if (coord_bary_u < 0.0 || coord_bary_u > 1.0)
        return false;
    Math::Vector3D value = o_radius.cross(c1);
    double second_coord_bary_v = force * ray._direction.dot(value);
    if (second_coord_bary_v < 0.0 || coord_bary_u + second_coord_bary_v > 1.0)
        return false;
    double position_t = force * c2.dot(value);
    if (position_t > EPSILON) {
        intersection.distance = position_t;
        intersection.position = ray._origin + ray._direction * position_t;
        Math::Vector3D normal = c1.cross(c2);
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
    return false;
}

Math::Point3D Triangle::getV0()
{
    return _v0;
}

Math::Point3D Triangle::getV1()
{
    return _v1;
}

Math::Point3D Triangle::getV2()
{
    return _v2;
}


bool Triangle::boundingBox(AABB &box) const
{
    Math::Point3D minimum(std::min({_v0._x, _v1._x, _v2._x}),
        std::min({_v0._y, _v1._y, _v2._y}), std::min({_v0._z, _v1._z, _v2._z}));
    Math::Point3D maximum(std::max({_v0._x, _v1._x, _v2._x}),
        std::max({_v0._y, _v1._y, _v2._y}), std::max({_v0._z, _v1._z, _v2._z}));

    if (maximum._x - minimum._x < EPSILON) {
        minimum._x -= EPSILON;
        maximum._x += EPSILON;
    }
    if (maximum._y - minimum._y < EPSILON) {
        minimum._y -= EPSILON;
        maximum._y += EPSILON;
    }
    if (maximum._z - minimum._z < EPSILON) {
        minimum._z -= EPSILON;
        maximum._z += EPSILON;
    }
    box = AABB(minimum, maximum);
    return true;
}
}
