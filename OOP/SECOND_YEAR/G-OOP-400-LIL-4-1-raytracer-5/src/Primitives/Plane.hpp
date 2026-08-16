/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "MathConstants.hpp"
#include "MathUtils.hpp"

namespace RayTracer {

class Plane : public IPrimitive
{
    private:
        Math::Point3D _point;
        Math::Vector3D _rotation;
        Math::Vector3D _normal;
        const IMaterial *_material;
    public:
        Plane();
        Plane(Math::Point3D point, Math::Vector3D rotation, Math::Vector3D normal, const IMaterial *material);
        ~Plane() = default;
        bool hit(const RayTracer::Ray &ray, Intersection &intersection) const override;
        bool boundingBox(AABB &box) const override;
};

}

#endif /* !PLANE_HPP_ */
