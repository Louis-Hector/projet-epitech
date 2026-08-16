/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Intersection
*/

#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
class IMaterial;
class Intersection
{
    public:
        Intersection();
        ~Intersection() = default;

        double distance;
        Math::Point3D position;
        Math::Vector3D surface_normal;
        const IMaterial *material;
};

}

#endif /* !INTERSECTION_HPP_ */
