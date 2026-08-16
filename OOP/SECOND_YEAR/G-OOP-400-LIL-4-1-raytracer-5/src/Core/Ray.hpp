/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
class Ray
{
    public:
        Ray();
        Ray(const Math::Point3D &point, const Math::Vector3D &vector);
        ~Ray() = default;

        Math::Point3D _origin;
        Math::Vector3D _direction;
};
}

#endif /* !RAY_HPP_ */
