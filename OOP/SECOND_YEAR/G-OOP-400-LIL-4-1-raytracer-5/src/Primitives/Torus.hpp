/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Torus
*/

#ifndef TORUS_HPP_
#define TORUS_HPP_

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "IPrimitive.hpp"
#include "MathConstants.hpp"
#include <algorithm>
#include <vector>

namespace RayTracer {

    class Torus : public IPrimitive
    {
    private:
        Math::Point3D _origin;
        double _radius_torus;
        double _radius_tube;
        const IMaterial *_material;
    public:
        Torus(/* args */);
        Torus(Math::Point3D origin, double radius_torus, double radius_tube, const IMaterial *material);
        ~Torus() = default;
        bool hit(const Ray &ray, Intersection &intersection) const override;
        bool boundingBox(AABB &box) const override;
    };
}

#endif /* !TORUS_HPP_ */
