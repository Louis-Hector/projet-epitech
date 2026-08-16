/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Pyramid
*/

#ifndef PYRAMID_HPP_
#define PYRAMID_HPP_

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "IPrimitive.hpp"
#include "Triangle.hpp"
#include <vector>

namespace RayTracer {
    class Pyramid : public IPrimitive {
    private:
        Math::Point3D _top;
        Math::Point3D _b0;
        Math::Point3D _b1;
        Math::Point3D _b2;
        Math::Point3D _b3;
        const IMaterial *_material;
    public:
        Pyramid(/* args */);
        Pyramid(Math::Point3D top, Math::Point3D b0, Math::Point3D b1, Math::Point3D b2, Math::Point3D b3, const IMaterial *material);
        ~Pyramid() = default;
        void create_pyramid(std::vector<Triangle> &form) const;
        bool hit(const Ray &ray, Intersection &intersection) const override;
        bool boundingBox(AABB &box) const override;
    };
}

#endif /* !PYRAMID_HPP_ */
