/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_

#include "ILight.hpp"

namespace RayTracer {

class PointLight : public ILight
{
    private:
        Math::Point3D _position;
        double _intensity;
        Color _color;
    public:
        PointLight();
        PointLight(const Math::Point3D &position, double intensity, const Color &color);
        ~PointLight() = default;

        Math::Vector3D getDirectionFrom(const Math::Point3D &point) const override;
        double getDistanceFrom(const Math::Point3D &point) const override;
        double getIntensity() const override;
        Color getColor() const override;
};

}

#endif /* !POINTLIGHT_HPP_ */
