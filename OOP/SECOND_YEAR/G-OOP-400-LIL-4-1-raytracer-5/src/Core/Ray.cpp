/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Ray
*/

#include "Ray.hpp"

namespace RayTracer {

Ray::Ray() : _origin(), _direction()
{
}

Ray::Ray(const Math::Point3D &point, const Math::Vector3D &vector) :
    _origin(point), _direction(vector)
{
}

}
