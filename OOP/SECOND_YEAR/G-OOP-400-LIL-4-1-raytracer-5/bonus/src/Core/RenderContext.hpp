/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** RenderContext
*/

#ifndef RENDERCONTEXT_HPP_
#define RENDERCONTEXT_HPP_

#include "Camera.hpp"
#include "RenderConfig.hpp"
#include "Scene.hpp"

namespace RayTracer {

struct RenderContext
{
    const Scene &scene;
    const Camera &camera;
    const RenderConfig &config;
};

}

#endif /* !RENDERCONTEXT_HPP_ */
