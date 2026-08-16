/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Builder
*/

#ifndef BUILDER_HPP_
#define BUILDER_HPP_

#include <unordered_map>
#include <libconfig.h++>
#include "Scene.hpp"
#include "Factory.hpp"
#include "MaterialFactory.hpp"

class RayBuilder
{
private:
    RayTracer::Scene _scene;
    Factory _primitive_factory;
    MaterialFactory _material_factory;
    std::unordered_map<std::string, const RayTracer::IMaterial *> _materials_by_name;
    const RayTracer::IMaterial *registerMaterial(libconfig::Setting &param_material);
    const RayTracer::IMaterial *getPrimitiveMaterial(libconfig::Setting &param_shape);
public:
    RayBuilder(/* args */);
    ~RayBuilder() = default;
    RayBuilder &appendCamera(libconfig::Setting &param_camera);
    RayBuilder &appendSettings(libconfig::Setting &param_settings);
    RayBuilder &appendMaterial(libconfig::Setting &param_material);
    RayBuilder &appendPrimitive(const char *name_primitive, libconfig::Setting &param_shape);
    RayBuilder &appendLight(const char *name_light, libconfig::Setting &param_light);
    RayTracer::Scene build();
};

#endif /* !BUILDER_HPP_ */
