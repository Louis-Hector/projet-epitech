/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Metal
*/

#ifndef METAL_HPP_
#define METAL_HPP_

#include "IMaterial.hpp"

namespace RayTracer {

class Metal : public IMaterial
{
    private:
        Color _color;
        double _fuzz;
    public:
        Metal();
        explicit Metal(const Color &color);
        Metal(const Color &color, double fuzz);
        ~Metal() override = default;
        Color getAlbedo() const override;
        bool isDelta() const override;
        bool transmitsLight() const override;
        Color getLightTransmission() const override;
        bool scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const override;
        bool scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

}

#endif /* !METAL_HPP_ */
