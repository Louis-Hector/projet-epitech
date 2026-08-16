/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "Color.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"

namespace RayTracer {

class IMaterial
{
    public:
        virtual ~IMaterial() = default;
        virtual Color getAlbedo() const = 0;
        virtual Color emit() const
        {
            return Color();
        }
        virtual bool isDelta() const = 0;
        virtual bool transmitsLight() const = 0;
        virtual Color getLightTransmission() const = 0;
        virtual bool scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const = 0;
        virtual bool scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const = 0;
};

}

#endif /* !IMATERIAL_HPP_ */
