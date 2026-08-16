/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Mobius
*/

#ifndef MOBIUS_HPP_
#define MOBIUS_HPP_

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "IPrimitive.hpp"
#include "AABB.hpp"
#include "MathConstants.hpp"

namespace RayTracer
{
    class Mobius : public IPrimitive
    {
        private:
            Math::Point3D _origin;
            double _radius;
            const IMaterial *_material;
            void calculateEquation(const Math::Vector3D &origin, const Math::Vector3D &direction, double &a, double &b, double &c, double &d) const;
            bool isInMobius(const Math::Vector3D &point) const;
            Math::Vector3D calculateNormal(const Math::Vector3D &point) const;

        public:
            Mobius();
            Mobius(Math::Point3D origin, double radius, const IMaterial *material);
            ~Mobius() = default;
            bool hit(const Ray &ray, Intersection &intersection) const override;
            bool boundingBox(AABB &box) const override;
    };

}

#endif /* !MOBIUS_HPP_ */
