/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Pyramid
*/

#include "Pyramid.hpp"
#include <algorithm>

namespace RayTracer {

Pyramid::Pyramid() : _top(), _b0(), _b1(), _b2(), _b3(), _material()
{
}

Pyramid::Pyramid(Math::Point3D top, Math::Point3D b0, Math::Point3D b1, Math::Point3D b2, Math::Point3D b3, const IMaterial *material) : _top(top),
    _b0(b0), _b1(b1), _b2(b2), _b3(b3), _material(material)
{
}

void Pyramid::create_pyramid(std::vector<Triangle> &form) const
{
    form.push_back({_top, _b0, _b1, _material});
    form.push_back({_top, _b1, _b2, _material});
    form.push_back({_top, _b2, _b3, _material});
    form.push_back({_top, _b3, _b0, _material});
    form.push_back({_b0, _b1, _b2, _material});
    form.push_back({_b0, _b2, _b3, _material});
}

bool Pyramid::hit(const Ray &ray, Intersection &intersection) const
{
    std::vector<Triangle> form;

    create_pyramid(form);
    bool pyramid_hit = false;
    Intersection inter_touch = {};
    double minimal_dist = 1000.0;
    for (const auto &triangle : form) {
        if (triangle.hit(ray, inter_touch)) {
            if (inter_touch.distance < minimal_dist) {
                minimal_dist = inter_touch.distance;
                pyramid_hit = true;
                intersection = inter_touch;
            }
        }
    }
    return pyramid_hit;
}

bool Pyramid::boundingBox(AABB &box) const
{
    Math::Point3D minimum(std::min({_top._x, _b0._x, _b1._x, _b2._x, _b3._x}),
        std::min({_top._y, _b0._y, _b1._y, _b2._y, _b3._y}), std::min({_top._z, _b0._z, _b1._z, _b2._z, _b3._z}));
    Math::Point3D maximum(std::max({_top._x, _b0._x, _b1._x, _b2._x, _b3._x}),
        std::max({_top._y, _b0._y, _b1._y, _b2._y, _b3._y}), std::max({_top._z, _b0._z, _b1._z, _b2._z, _b3._z}));

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
