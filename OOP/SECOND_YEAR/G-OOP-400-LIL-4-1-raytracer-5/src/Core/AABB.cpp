/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** AABB
*/

#include "AABB.hpp"
#include "MathConstants.hpp"
#include <cmath>
#include <limits>

namespace RayTracer {

AABB::AABB() : min(), max()
{
}

AABB::AABB(const Math::Point3D &minimum, const Math::Point3D &maximum) : min(minimum), max(maximum)
{
}

Math::Point3D AABB::centroid() const
{
    return Math::Point3D((min._x + max._x) * 0.5, (min._y + max._y) * 0.5, (min._z + max._z) * 0.5);
}

double AABB::entryDistance(const Ray &ray, double t_min, double t_max) const
{
    const double origins[3] = {ray._origin._x, ray._origin._y, ray._origin._z};
    const double directions[3] = {ray._direction._x, ray._direction._y, ray._direction._z};
    const double minimums[3] = {min._x, min._y, min._z};
    const double maximums[3] = {max._x, max._y, max._z};

    for (int axis = 0; axis < 3; axis++) {
        if (std::fabs(directions[axis]) <= EPSILON) {
            if (origins[axis] < minimums[axis] || origins[axis] > maximums[axis])
                return std::numeric_limits<double>::infinity();
            continue;
        }
        const double inverse_direction = 1.0 / directions[axis];
        double axis_min = (minimums[axis] - origins[axis]) * inverse_direction;
        double axis_max = (maximums[axis] - origins[axis]) * inverse_direction;
        if (inverse_direction < 0.0)
            std::swap(axis_min, axis_max);
        t_min = std::max(axis_min, t_min);
        t_max = std::min(axis_max, t_max);
        if (t_max <= t_min)
            return std::numeric_limits<double>::infinity();
    }
    return t_min;
}

bool AABB::hit(const Ray &ray, double t_min, double t_max) const
{
    return std::isfinite(entryDistance(ray, t_min, t_max));
}

AABB AABB::surroundingBox(const AABB &left, const AABB &right)
{
    return AABB(Math::Point3D(std::min(left.min._x, right.min._x), std::min(left.min._y, right.min._y), std::min(left.min._z, right.min._z)),
        Math::Point3D(std::max(left.max._x, right.max._x), std::max(left.max._y, right.max._y), std::max(left.max._z, right.max._z)));
}

}
