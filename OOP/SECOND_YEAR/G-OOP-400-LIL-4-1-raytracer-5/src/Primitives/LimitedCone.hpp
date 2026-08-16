/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** LimitedCone
*/

#ifndef LIMITEDCONE_HPP_
#define LIMITEDCONE_HPP_

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "IPrimitive.hpp"
#include "AABB.hpp"
#include "MathConstants.hpp"
#include <cmath>

namespace RayTracer
{
    class LimitedCone : public IPrimitive
    {
        private:
            Math::Point3D _top;
            double _angle;
            double _height;
            const IMaterial *_material;
            bool hitBody(const Ray &ray, Intersection &intersection) const;
            bool hitBase(const Ray &ray, Intersection &intersection) const;
            Math::Vector3D computeNormal(const Math::Vector3D &localPoint) const;

        public:
            LimitedCone();
            LimitedCone(Math::Point3D top, double angle, double height, const IMaterial *material);
            ~LimitedCone() = default;
            bool hit(const Ray &ray, Intersection &intersection) const override;
            bool boundingBox(AABB &box) const override;
    };
}

#endif /* !LIMITEDCONE_HPP_ */
