/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** RenderConfig
*/

#ifndef RENDERCONFIG_HPP_
#define RENDERCONFIG_HPP_

#include "Color.hpp"

namespace RayTracer {

struct RenderConfig
{
    int samples_per_pixel;
    int max_ray_depth;
    bool ambient_occlusion_enabled;
    Color background_color;
};

}

#endif /* !RENDERCONFIG_HPP_ */
