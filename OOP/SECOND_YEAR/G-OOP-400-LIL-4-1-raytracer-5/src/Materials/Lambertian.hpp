/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
#define LAMBERTIAN_HPP_

#include "IMaterial.hpp"

namespace RayTracer {

class Lambertian : public IMaterial
{
    private:
        Color _color;
    public:
        Lambertian();
        explicit Lambertian(const Color &color);
        ~Lambertian() override = default;
        Color getAlbedo() const override;
        bool isDelta() const override;
        bool transmitsLight() const override;
        Color getLightTransmission() const override;
        bool scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const override;
        bool scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

}

#endif /* !LAMBERTIAN_HPP_ */
