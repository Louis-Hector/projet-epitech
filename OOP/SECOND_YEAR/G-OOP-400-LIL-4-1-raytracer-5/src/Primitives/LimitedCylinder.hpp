/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** LimitedCylinder
*/

#ifndef LIMITEDCYLINDER_HPP_
#define LIMITEDCYLINDER_HPP_

#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "Point3D.hpp"
#include "MathConstants.hpp"
#include <cmath>

namespace RayTracer {
    class LimitedCylinder : public IPrimitive
    {
        private:
            Math::Point3D _center;
            double _height;
            double _radius;
            const IMaterial *_material;
            bool inBounds(const RayTracer::Ray &ray, double t) const;
            bool intersectSide(const RayTracer::Ray &ray, Intersection &intersection) const;
            bool intersectCap(const RayTracer::Ray &ray, double cap_y,
                double normal_y, Intersection &intersection) const;
        public:
            LimitedCylinder();
            LimitedCylinder(Math::Point3D center, double height, double radius, const IMaterial *material);
            ~LimitedCylinder() = default;
            bool hit(const RayTracer::Ray &ray, Intersection &intersection) const override;
            bool boundingBox(AABB &box) const override;
    };
}

#endif /* !LIMITEDCYLINDER_HPP_ */
