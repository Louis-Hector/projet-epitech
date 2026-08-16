/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Emissive
*/

#ifndef EMISSIVE_HPP_
#define EMISSIVE_HPP_

#include "IMaterial.hpp"

namespace RayTracer {

class Emissive : public IMaterial
{
    private:
        Color _color;
        double _intensity;
    public:
        Emissive();
        Emissive(const Color &color, double intensity);
        ~Emissive() override = default;

        Color getAlbedo() const override;
        Color emit() const override;
        bool isDelta() const override;
        bool transmitsLight() const override;
        Color getLightTransmission() const override;
        bool scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const override;
        bool scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

}

#endif /* !EMISSIVE_HPP_ */
