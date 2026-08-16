/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** SpotLight
*/

#ifndef SPOTLIGHT_HPP_
#define SPOTLIGHT_HPP_

#include "ILight.hpp"

namespace RayTracer {

class SpotLight : public ILight
{
    private:
        Math::Point3D _position;
        Math::Vector3D _direction;
        double _angle;
        double _intensity;
        Color _color;
    public:
        SpotLight();
        SpotLight(const Math::Point3D &position, const Math::Vector3D &direction,
            double angle, double intensity, const Color &color);
        ~SpotLight() = default;

        Math::Vector3D getDirectionFrom(const Math::Point3D &point) const override;
        double getDistanceFrom(const Math::Point3D &point) const override;
        double getIntensity() const override;
        Color getColor() const override;
        Math::Point3D getPosition() const;
        Math::Vector3D getAxisDirection() const;
        double getAngle() const;
};

}

#endif /* !SPOTLIGHT_HPP_ */
