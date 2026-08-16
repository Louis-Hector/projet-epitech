/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "MathConstants.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    class Triangle : public IPrimitive
    {
    private:
        Math::Point3D _v0;
        Math::Point3D _v1;
        Math::Point3D _v2;
        const IMaterial *_material;
    public:
        Triangle(/* args */);
        Triangle(Math::Point3D A, Math::Point3D B, Math::Point3D C, const IMaterial *material);
        ~Triangle() = default;
        Math::Point3D getV0();
        Math::Point3D getV1();
        Math::Point3D getV2();
        bool hit(const Ray &ray, Intersection &intersection) const override;
        bool boundingBox(AABB &box) const override;
    };
}

#endif /* !TRIANGLE_HPP_ */
