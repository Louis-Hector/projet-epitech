/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "IPrimitive.hpp"
#include "AABB.hpp"
#include "MathConstants.hpp"
#include "MathUtils.hpp"
#include <cmath>

namespace RayTracer
{
    class Cone : public IPrimitive
    {
        private:
            Math::Point3D _top;
            Math::Vector3D _rotation;
            double _angle;
            const IMaterial *_material;
            Math::Vector3D computeNormal(const Math::Vector3D &intersectionPoint) const;

        public:
            Cone();
            Cone(Math::Point3D top, Math::Vector3D rotation, double angle, const IMaterial *material);
            ~Cone() = default;
            bool hit(const Ray &ray, Intersection &intersection) const override;
            bool boundingBox(AABB &box) const override;
    };
}

#endif /* !CONE_HPP_ */
