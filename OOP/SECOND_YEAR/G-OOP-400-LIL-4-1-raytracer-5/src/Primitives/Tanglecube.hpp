/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Tanglecube
*/

#ifndef TANGLECUBE_HPP_
#define TANGLECUBE_HPP_

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "IPrimitive.hpp"
#include "MathConstants.hpp"

namespace RayTracer {

    class Tanglecube : public IPrimitive
    {
    private:
        Math::Point3D _origin;
        double _scale;
        const IMaterial *_material;
    public:
        Tanglecube(/* args */);
        Tanglecube(Math::Point3D origin, double scale, const IMaterial *material);
        ~Tanglecube() = default;
        bool hit(const Ray &ray, Intersection &intersection) const override;
        bool boundingBox(AABB &box) const override;
    };
}

#endif /* !TANGLECUBE_HPP_ */
