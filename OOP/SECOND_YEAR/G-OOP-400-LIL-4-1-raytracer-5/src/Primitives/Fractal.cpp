/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Fractal
*/

#include "Fractal.hpp"
#include <limits>

namespace RayTracer {

Math::Point3D Fractal::get_center(const Math::Point3D &a, const Math::Point3D &b)
{
    double x = (a._x + b._x) / 2;
    double y = (a._y + b._y) / 2;
    double z = (a._z + b._z) / 2;

    return Math::Point3D(x, y, z);
}

Fractal::Fractal() : _material(nullptr), _depth(0)
{
}

Fractal::Fractal(Math::Point3D top, Math::Point3D b0, Math::Point3D b1, Math::Point3D b2, Math::Point3D b3, int depth, const IMaterial *material) : _material(material), _depth(depth)
{
    recursive_build_fractal(top, b0, b1, b2, b3, depth);
}

Fractal::~Fractal()
{
}

void Fractal::recursive_build_fractal(Math::Point3D top, Math::Point3D b0, Math::Point3D b1, Math::Point3D b2, Math::Point3D b3, int depth)
{
    if (depth == 0) {
        Pyramid pyramid(top, b0, b1, b2, b3, _material);
        pyramid.create_pyramid(_triangles);
        return;
    }
    Math::Point3D center_top_b0 = get_center(top, b0);
    Math::Point3D center_top_b1 = get_center(top, b1);
    Math::Point3D center_top_b2 = get_center(top, b2);
    Math::Point3D center_top_b3 = get_center(top, b3);
    Math::Point3D center_b0_b1 = get_center(b0, b1);
    Math::Point3D center_b1_b2 = get_center(b1, b2);
    Math::Point3D center_b2_b3 = get_center(b2, b3);
    Math::Point3D center_b3_b0 = get_center(b3, b0);
    Math::Point3D center_base = get_center(get_center(b0, b2), get_center(b1, b3));
    recursive_build_fractal(top, center_top_b0, center_top_b1, center_top_b2, center_top_b3, depth - 1);
    recursive_build_fractal(center_top_b0, b0, center_b0_b1, center_base, center_b3_b0, depth - 1);
    recursive_build_fractal(center_top_b1, center_b0_b1, b1, center_b1_b2, center_base, depth - 1);
    recursive_build_fractal(center_top_b2, center_base, center_b1_b2, b2, center_b2_b3, depth - 1);
    recursive_build_fractal(center_top_b3, center_b3_b0, center_base, center_b2_b3, b3, depth - 1);
}


bool Fractal::hit(const Ray &ray, Intersection &intersection) const
{
    bool is_hit = false;
    Intersection temp = {};
    double min_dist = std::numeric_limits<double>::max();

    for (const auto &triangle : _triangles) {
        if (triangle.hit(ray, temp)) {
            if (temp.distance < min_dist) {
                min_dist = temp.distance;
                intersection = temp;
                is_hit = true;
            }
        }
    }
    return is_hit;
}

bool Fractal::boundingBox(AABB &box) const
{
    if (_triangles.empty())
        return false;
    AABB triangle_box;
    bool found_box = false;

    for (const Triangle &triangle : _triangles) {
        if (!triangle.boundingBox(triangle_box))
            continue;
        if (!found_box) {
            box = triangle_box;
            found_box = true;
            continue;
        }
        box = AABB::surroundingBox(box, triangle_box);
    }
    return found_box;
}

}
