/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include "AABB.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"

namespace RayTracer {

class IPrimitive
{
    public:
        virtual ~IPrimitive() = default;
        virtual bool hit(const Ray &ray, Intersection &intersection) const = 0;
        virtual bool boundingBox(AABB &box) const = 0;
};

}

#endif /* !IPRIMITIVE_HPP_ */
