/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include "Color.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {

class ILight
{
    public:
        virtual ~ILight() = default;
        virtual Math::Vector3D getDirectionFrom(const Math::Point3D &point) const = 0;
        virtual double getDistanceFrom(const Math::Point3D &point) const = 0;
        virtual double getIntensity() const = 0;
        virtual Color getColor() const = 0;
};

}

#endif /* !ILIGHT_HPP_ */
