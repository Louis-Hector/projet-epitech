/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Dielectric
*/

#ifndef DIELECTRIC_HPP_
#define DIELECTRIC_HPP_

#include "IMaterial.hpp"

namespace RayTracer {

class Dielectric : public IMaterial
{
    private:
        Color _color;
        double _refraction_index;
        double _transparency;
    public:
        Dielectric();
        Dielectric(const Color &color, double refraction_index, double transparency);
        ~Dielectric() override = default;

        Color getAlbedo() const override;
        bool isDelta() const override;
        bool transmitsLight() const override;
        Color getLightTransmission() const override;
        bool scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const override;
        bool scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

}

#endif /* !DIELECTRIC_HPP_ */
