/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_HPP_
#define DIRECTIONALLIGHT_HPP_

#include "ILight.hpp"

namespace RayTracer {

class DirectionalLight : public ILight
{
    private:
        Math::Vector3D _direction;
        double _intensity;
        Color _color;
    public:
        DirectionalLight();
        DirectionalLight(const Math::Vector3D &direction, double intensity, const Color &color);
        ~DirectionalLight() = default;

        Math::Vector3D getDirectionFrom(const Math::Point3D &point) const override;
        double getDistanceFrom(const Math::Point3D &point) const override;
        double getIntensity() const override;
        Color getColor() const override;
};

}

#endif /* !DIRECTIONALLIGHT_HPP_ */
