/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Intersection
*/

#include <limits>
#include "Intersection.hpp"

namespace RayTracer {

Intersection::Intersection() :
    distance(std::numeric_limits<double>::max()), position(), surface_normal(), material(nullptr)
{
}

}
