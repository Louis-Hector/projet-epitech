/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "Point3D.hpp"
#include "MathConstants.hpp"
#include "MathUtils.hpp"
#include <cmath>

namespace RayTracer {
    class Cylinder : public IPrimitive
    {
        private:
            Math::Point3D _center;
            Math::Vector3D _rotation;
            double _radius;
            const IMaterial *_material;
        public:
            Cylinder();
            Cylinder(Math::Point3D center, Math::Vector3D rotation, double radius, const IMaterial *material);
            ~Cylinder() = default;
            bool hit(const RayTracer::Ray &ray, Intersection &intersection) const override;
            bool boundingBox(AABB &box) const override;
    };
}

#endif /* !CYLINDER_HPP_ */
