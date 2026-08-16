/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transparent
*/

#ifndef TRANSPARENT_HPP_
#define TRANSPARENT_HPP_

#include "IMaterial.hpp"

namespace RayTracer {

class Transparent : public IMaterial
{
    public:
        Transparent() = default;
        ~Transparent() override = default;

        Color getAlbedo() const override;
        bool isDelta() const override;
        bool transmitsLight() const override;
        Color getLightTransmission() const override;
        bool scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const override;
        bool scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

}

#endif /* !TRANSPARENT_HPP_ */
