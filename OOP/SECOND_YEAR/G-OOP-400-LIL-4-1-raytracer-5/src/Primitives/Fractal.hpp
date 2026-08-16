/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Fractal
*/

#ifndef FRACTAL_HPP_
#define FRACTAL_HPP_

#include <vector>
#include "Pyramid.hpp"
#include "Triangle.hpp"
#include "AABB.hpp"
#include "IMaterial.hpp"
#include "Point3D.hpp"
#include "IPrimitive.hpp"

namespace RayTracer
{
    class Fractal : public IPrimitive
    {
        private:
            void recursive_build_fractal(Math::Point3D top, Math::Point3D b0, Math::Point3D b1, Math::Point3D b2, Math::Point3D b3, int depth);
            static Math::Point3D get_center(const Math::Point3D &a, const Math::Point3D &b);
            std::vector<Triangle> _triangles;
            const IMaterial *_material;
            int _depth;
        public:
            Fractal();
            Fractal(Math::Point3D top, Math::Point3D b0, Math::Point3D b1, Math::Point3D b2, Math::Point3D b3, int depth, const IMaterial *material);
            ~Fractal();
            bool hit(const Ray &ray, Intersection &intersection) const override;
            bool boundingBox(AABB &box) const override;
    };
}

#endif /* !FRACTAL_HPP_ */
