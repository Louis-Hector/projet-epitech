/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** AABB
*/

#ifndef AABB_HPP_
#define AABB_HPP_

#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer {

class AABB
{
    public:
        Math::Point3D min;
        Math::Point3D max;

        AABB();
        AABB(const Math::Point3D &minimum, const Math::Point3D &maximum);
        Math::Point3D centroid() const;
        bool hit(const Ray &ray, double t_min, double t_max) const;
        double entryDistance(const Ray &ray, double t_min, double t_max) const;
        static AABB surroundingBox(const AABB &left, const AABB &right);
};

}

#endif /* !AABB_HPP_ */
