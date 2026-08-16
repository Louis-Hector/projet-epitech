/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Factory
*/

#include "Factory.hpp"
#include "Cylinder.hpp"
#include "DirectionalLight.hpp"
#include "LimitedCylinder.hpp"
#include "Plane.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "RayTracerError.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Pyramid.hpp"
#include "Torus.hpp"
#include "Fractal.hpp"
#include "Cone.hpp"
#include "LimitedCone.hpp"
#include "Mobius.hpp"
#include "Tanglecube.hpp"
#include "Obj.hpp"

Factory::Factory()
{
    builders = {
        {"spheres", &Factory::buildSphere},
        {"cylinders", &Factory::buildCylinder},
        {"limitedCylinders", &Factory::buildLimitedCylinder},
        {"planes", &Factory::buildPlane},
        {"triangles", &Factory::buildTriangle},
        {"pyramids", &Factory::buildPyramid},
        {"torus", &Factory::buildTorus},
        {"fractals", &Factory::buildFractal},
        {"cones", &Factory::buildCone},
        {"limitedCones", &Factory::buildLimitedCone},
        {"mobius", &Factory::buildMobius},
        {"tanglecube", &Factory::buildTanglecube},
        {"obj", &Factory::buildObj}
    };
}

static RayTracer::Color getColorFromSetting(libconfig::Setting &setting)
{
    int red = 255;
    int green = 255;
    int blue = 255;

    setting.lookupValue("r", red);
    setting.lookupValue("g", green);
    setting.lookupValue("b", blue);
    return RayTracer::Color(red, green, blue);
}

std::vector<double> Factory::getValuesDim(libconfig::Setting &setting, const char *name1, const char *name2, const char *name3)
{
    double x = {};
    double y = {};
    double z = {};
    setting.lookupValue(name1, x);
    setting.lookupValue(name2, y);
    setting.lookupValue(name3, z);
    return {x, y, z};
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildMobius(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_origin = getValuesDim(setting, "x", "y", "z");
    Math::Point3D origin(value_origin[0], value_origin[1], value_origin[2]);

    double radius = 1.0;
    double scale = 1.0;
    setting.lookupValue("radius", radius);
    setting.lookupValue("scale", scale);
    radius *= scale;
    return std::make_unique<RayTracer::Mobius>(origin, radius, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildLimitedCone(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_top = getValuesDim(setting, "x", "y", "z");
    Math::Point3D top(value_top[0], value_top[1], value_top[2]);

    double angle = 20.0;
    double height = 1.0;
    double scale = 1.0;
    setting.lookupValue("angle", angle);
    setting.lookupValue("height", height);
    setting.lookupValue("scale", scale);
    height *= scale;
    return std::make_unique<RayTracer::LimitedCone>(top, angle, height, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildCone(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_top = getValuesDim(setting, "x", "y", "z");
    std::vector<double> value_rotation = {0.0, 0.0, 0.0};
    if (setting.exists("rotation"))
        value_rotation = getValuesDim(setting["rotation"], "x", "y", "z");
    Math::Point3D top(value_top[0], value_top[1], value_top[2]);
    Math::Vector3D rotation(value_rotation[0], value_rotation[1], value_rotation[2]);

    double angle_degrees = 20.0;
    double scale = 1.0;
    setting.lookupValue("angle", angle_degrees);
    setting.lookupValue("scale", scale);
    return std::make_unique<RayTracer::Cone>(top, rotation, angle_degrees, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildFractal(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_top = getValuesDim(setting["top"], "x", "y", "z");
    std::vector<double> value_point1 = getValuesDim(setting["point1"], "x", "y", "z");
    std::vector<double> value_point2 = getValuesDim(setting["point2"], "x", "y", "z");
    std::vector<double> value_point3 = getValuesDim(setting["point3"], "x", "y", "z");
    std::vector<double> value_point4 = getValuesDim(setting["point4"], "x", "y", "z");
    Math::Point3D top(value_top[0], value_top[1], value_top[2]);
    Math::Point3D b0(value_point1[0], value_point1[1], value_point1[2]);
    Math::Point3D b1(value_point2[0], value_point2[1], value_point2[2]);
    Math::Point3D b2(value_point3[0], value_point3[1], value_point3[2]);
    Math::Point3D b3(value_point4[0], value_point4[1], value_point4[2]);

    double scale = 1;
    setting.lookupValue("scale", scale);
    top._x *= scale;
    top._y *= scale;
    top._z *= scale;
    b0._x *= scale;
    b0._y *= scale;
    b0._z *= scale;
    b1._x *= scale;
    b1._y *= scale;
    b1._z *= scale;
    b2._x *= scale;
    b2._y *= scale;
    b2._z *= scale;
    b3._x *= scale;
    b3._y *= scale;
    b3._z *= scale;
    int depth = 1;
    setting.lookupValue("depth", depth);
    return std::make_unique<RayTracer::Fractal>(top, b0, b1, b2, b3, depth, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildSphere(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_center = getValuesDim(setting, "x", "y", "z");
    Math::Point3D center(value_center[0], value_center[1], value_center[2]);
    double radius = {};
    double scale = {1};

    setting.lookupValue("r", radius);
    setting.lookupValue("scale", scale);
    radius *= scale;
    return std::make_unique<RayTracer::Sphere>(center, radius, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildCylinder(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_center = getValuesDim(setting, "x", "y", "z");
    std::vector<double> value_rotation = {0.0, 0.0, 0.0};
    if (setting.exists("rotation"))
        value_rotation = getValuesDim(setting["rotation"], "x", "y", "z");
    Math::Point3D center(value_center[0], value_center[1], value_center[2]);
    Math::Vector3D rotation(value_rotation[0], value_rotation[1], value_rotation[2]);
    double radius = {};
    double scale = {1};

    setting.lookupValue("radius", radius);
    setting.lookupValue("scale", scale);
    radius *= scale;
    return std::make_unique<RayTracer::Cylinder>(center, rotation, radius, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildLimitedCylinder(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_center = getValuesDim(setting, "x", "y", "z");
    Math::Point3D center(value_center[0], value_center[1], value_center[2]);
    double radius = {};
    double height = {};
    double scale = {1};

    setting.lookupValue("radius", radius);
    setting.lookupValue("height", height);
    setting.lookupValue("scale", scale);
    radius *= scale;
    height *= scale;
    return std::make_unique<RayTracer::LimitedCylinder>(center, height, radius, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildPlane(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_point = getValuesDim(setting, "x", "y", "z");
    Math::Point3D point(value_point[0], value_point[1], value_point[2]);
    libconfig::Setting &list_normal = setting["normal"];
    std::vector<double> value_normal = getValuesDim(list_normal, "x", "y", "z");
    Math::Vector3D normal(value_normal[0], value_normal[1], value_normal[2]);
    std::vector<double> value_rotation = {0.0, 0.0, 0.0};
    if (setting.exists("rotation"))
        value_rotation = getValuesDim(setting["rotation"], "x", "y", "z");
    Math::Vector3D rotation(value_rotation[0], value_rotation[1], value_rotation[2]);
    return std::make_unique<RayTracer::Plane>(point, rotation, normal, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildTriangle(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_point1 = getValuesDim(setting["point1"], "x", "y", "z");
    std::vector<double> value_point2 = getValuesDim(setting["point2"], "x", "y", "z");
    std::vector<double> value_point3 = getValuesDim(setting["point3"], "x", "y", "z");
    Math::Point3D point1(value_point1[0], value_point1[1], value_point1[2]);
    Math::Point3D point2(value_point2[0], value_point2[1], value_point2[2]);
    Math::Point3D point3(value_point3[0], value_point3[1], value_point3[2]);
    double scale = {1};

    setting.lookupValue("scale", scale);
    point1._x *= scale;
    point1._y *= scale;
    point2._x *= scale;
    point2._y *= scale;
    point3._x *= scale;
    point3._y *= scale;
    return std::make_unique<RayTracer::Triangle>(point1, point2, point3, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildPyramid(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_top = getValuesDim(setting["top"], "x", "y", "z");
    std::vector<double> value_point1 = getValuesDim(setting["point1"], "x", "y", "z");
    std::vector<double> value_point2 = getValuesDim(setting["point2"], "x", "y", "z");
    std::vector<double> value_point3 = getValuesDim(setting["point3"], "x", "y", "z");
    std::vector<double> value_point4 = getValuesDim(setting["point4"], "x", "y", "z");
    Math::Point3D top(value_top[0], value_top[1], value_top[2]);
    Math::Point3D b0(value_point1[0], value_point1[1], value_point1[2]);
    Math::Point3D b1(value_point2[0], value_point2[1], value_point2[2]);
    Math::Point3D b2(value_point3[0], value_point3[1], value_point3[2]);
    Math::Point3D b3(value_point4[0], value_point4[1], value_point4[2]);

    double scale = {1};

    setting.lookupValue("scale", scale);
    top._y *= scale;
    b0._x *= scale;
    b1._x *= scale;
    b2._x *= scale;
    b3._x *= scale;
    return std::make_unique<RayTracer::Pyramid>(top, b0, b1, b2, b3, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildTorus(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_origin = getValuesDim(setting, "x", "y", "z");
    Math::Point3D origin(value_origin[0], value_origin[1], value_origin[2]);
    double R = {};
    double r = {};
    double scale = 1;

    setting.lookupValue("circle", R);
    setting.lookupValue("tube", r);
    setting.lookupValue("scale", scale);
    R *= scale;
    r *= scale;
    return std::make_unique<RayTracer::Torus>(origin, R, r, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildTanglecube(libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    std::vector<double> value_origin = getValuesDim(setting, "x", "y", "z");
    Math::Point3D origin(value_origin[0], value_origin[1], value_origin[2]);
    double scale = 1.0;

    setting.lookupValue("scale", scale);
    if (scale <= 0.0)
        throw FactoryError("Tanglecube scale must be positive");
    return std::make_unique<RayTracer::Tanglecube>(origin, scale, material);
}

std::unique_ptr<RayTracer::IPrimitive> Factory::buildObj(libconfig::Setting &setting, [[maybe_unused]] const RayTracer::IMaterial *material)
{
    std::string path;
    std::vector<double> value_origin = getValuesDim(setting, "x", "y", "z");
    Math::Point3D origin(value_origin[0], value_origin[1], value_origin[2]);
    std::vector<double> value_rotation = {0.0, 0.0, 0.0};
    if (setting.exists("rotation"))
        value_rotation = getValuesDim(setting["rotation"], "x", "y", "z");

    setting.lookupValue("path", path);
    return std::make_unique<RayTracer::Obj>(path, origin, Math::Vector3D {value_rotation[0], value_rotation[1], value_rotation[2]});
}


std::unique_ptr<RayTracer::IPrimitive> Factory::createPrimitive(const std::string &name_element,
    libconfig::Setting &setting, const RayTracer::IMaterial *material)
{
    const auto element = builders.find(name_element);

    if (element == builders.end())
        throw FactoryError("Unknown primitive type: " + name_element);
    return (this->*(element->second))(setting, material);
}

std::unique_ptr<RayTracer::ILight> Factory::createLight(const std::string &name_element,
    libconfig::Setting &setting)
{
    if (name_element == "directional") {
        std::vector<double> value_direction = getValuesDim(setting, "x", "y", "z");
        Math::Vector3D direction(value_direction[0], value_direction[1], value_direction[2]);
        double intensity = {};
        RayTracer::Color color(255.0, 255.0, 255.0);

        setting.lookupValue("intensity", intensity);
        if (setting.exists("color"))
            color = getColorFromSetting(setting["color"]);
        return std::make_unique<RayTracer::DirectionalLight>(direction, intensity, color);
    }
    if (name_element == "point") {
        std::vector<double> value_position = getValuesDim(setting, "x", "y", "z");
        Math::Point3D position(value_position[0], value_position[1], value_position[2]);
        double intensity = {};
        RayTracer::Color color(255.0, 255.0, 255.0);

        setting.lookupValue("intensity", intensity);
        if (setting.exists("color"))
            color = getColorFromSetting(setting["color"]);
        return std::make_unique<RayTracer::PointLight>(position, intensity, color);
    }
    if (name_element == "spot") {
        std::vector<double> value_position = getValuesDim(setting, "x", "y", "z");
        Math::Point3D position(value_position[0], value_position[1], value_position[2]);
        libconfig::Setting &direction_setting = setting["direction"];
        std::vector<double> value_direction = getValuesDim(direction_setting, "x", "y", "z");
        Math::Vector3D direction(value_direction[0], value_direction[1], value_direction[2]);
        double angle = 30.0;
        double intensity = {};
        RayTracer::Color color(255.0, 255.0, 255.0);

        setting.lookupValue("angle", angle);
        setting.lookupValue("intensity", intensity);
        if (setting.exists("color"))
            color = getColorFromSetting(setting["color"]);
        return std::make_unique<RayTracer::SpotLight>(position, direction, angle, intensity, color);
    }
    throw FactoryError("Unknown light type: " + name_element);
}
