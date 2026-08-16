/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Builder
*/

#include "Builder.hpp"
#include "RayTracerError.hpp"
#include <algorithm>

RayBuilder::RayBuilder(/* args */) : _scene(), _primitive_factory(), _material_factory(), _materials_by_name()
{
}

RayBuilder &RayBuilder::appendCamera(libconfig::Setting &param_camera)
{
    double width = {};
    double height = {};
    libconfig::Setting &list_resolution = param_camera["resolution"];
    list_resolution.lookupValue("width", width);
    list_resolution.lookupValue("height", height);
    libconfig::Setting &list_position = param_camera["position"];
    double position_x = {};
    double position_y = {};
    double position_z = {};
    list_position.lookupValue("x", position_x);
    list_position.lookupValue("y", position_y);
    list_position.lookupValue("z", position_z);
    Math::Point3D origin(position_x, position_y, position_z);
    libconfig::Setting &list_rotation = param_camera["rotation"];
    double rotation_x = {};
    double rotation_y = {};
    double rotation_z = {};
    list_rotation.lookupValue("x", rotation_x);
    list_rotation.lookupValue("y", rotation_y);
    list_rotation.lookupValue("z", rotation_z);
    Math::Vector3D rotation(rotation_x, rotation_y, rotation_z);
    double fieldOfView = {};
    param_camera.lookupValue("fieldOfView", fieldOfView);
    RayTracer::Camera camera(origin, rotation, fieldOfView, width, height);
    _scene.addCamera(camera);
    return *this;
}

RayBuilder &RayBuilder::appendSettings(libconfig::Setting &param_settings)
{
    int samples_per_pixel = 100;
    int max_ray_depth = 10;
    int red = 127;
    int green = 178;
    int blue = 255;

    param_settings.lookupValue("SamplePerPixel", samples_per_pixel);
    param_settings.lookupValue("Max_Depth", max_ray_depth);
    if (param_settings.exists("background")) {
        libconfig::Setting &background = param_settings["background"];

        background.lookupValue("r", red);
        background.lookupValue("g", green);
        background.lookupValue("b", blue);
    }
    _scene.setRenderSettings(std::max(samples_per_pixel, 1), std::max(max_ray_depth, 1), RayTracer::Color(red, green, blue));
    return *this;
}

const RayTracer::IMaterial *RayBuilder::registerMaterial(libconfig::Setting &param_material)
{
    std::string material_name;

    if (!param_material.lookupValue("name", material_name))
        throw BuilderError("Material is missing its name");
    if (_materials_by_name.find(material_name) != _materials_by_name.end())
        throw BuilderError("Material already defined: " + material_name);
    std::unique_ptr<RayTracer::IMaterial> material_owner = _material_factory.createMaterial(param_material);
    if (material_owner == nullptr)
        throw BuilderError("Failed to create material: " + material_name);
    const RayTracer::IMaterial *material = _scene.addMaterial(std::move(material_owner));
    _materials_by_name[material_name] = material;
    return material;
}

RayBuilder &RayBuilder::appendMaterial(libconfig::Setting &param_material)
{
    registerMaterial(param_material);
    return *this;
}

const RayTracer::IMaterial *RayBuilder::getPrimitiveMaterial(libconfig::Setting &param_shape)
{
    std::string material_name;

    if (!param_shape.lookupValue("material", material_name))
        throw BuilderError("Primitive is missing its material reference");
    const auto material_it = _materials_by_name.find(material_name);
    if (material_it == _materials_by_name.end())
        throw BuilderError("Unknown material: " + material_name);
    return material_it->second;
}

RayBuilder &RayBuilder::appendPrimitive(const char *name_primitive, libconfig::Setting &param_shape)
{
    const RayTracer::IMaterial *material = getPrimitiveMaterial(param_shape);
    std::unique_ptr<RayTracer::IPrimitive> element = _primitive_factory.createPrimitive(name_primitive, param_shape, material);

    if (element != nullptr)
        _scene.addPrimitive(std::move(element));
    return *this;
}

RayBuilder &RayBuilder::appendLight(const char *name_light, libconfig::Setting &param_light)
{
    std::unique_ptr<RayTracer::ILight> element = _primitive_factory.createLight(name_light, param_light);

    if (element != nullptr)
        _scene.addLight(std::move(element));
    return *this;
}

RayTracer::Scene RayBuilder::build()
{
    return std::move(_scene);
}
