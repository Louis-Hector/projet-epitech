/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Mirror
*/

#ifndef MIRROR_HPP_
#define MIRROR_HPP_

#include "IMaterial.hpp"

namespace RayTracer {

class Mirror : public IMaterial
{
    private:
        Color _color;
    public:
        Mirror();
        explicit Mirror(const Color &color);
        ~Mirror() override = default;
        Color getAlbedo() const override;
        bool isDelta() const override;
        bool transmitsLight() const override;
        Color getLightTransmission() const override;
        bool scatterShadowRay(const Ray &ray, const Intersection &intersection, Color &transmission, Ray &scattered) const override;
        bool scatter(const Ray &ray, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

}

#endif /* !MIRROR_HPP_ */
