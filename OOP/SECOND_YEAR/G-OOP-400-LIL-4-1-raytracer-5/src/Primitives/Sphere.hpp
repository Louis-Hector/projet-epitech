/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "Point3D.hpp"
#include <cmath>

namespace RayTracer {
    class Sphere : public IPrimitive
    {
        private:
            Math::Point3D _center;
            double _radius;
            const IMaterial *_material;
        public:
            Sphere();
            Sphere(Math::Point3D center, double radius, const IMaterial *material);
            ~Sphere() = default;
            bool hit(const RayTracer::Ray &ray, Intersection &intersection) const override;
            bool boundingBox(AABB &box) const override;
    };
}

#endif /* !SPHERE_HPP_ */
