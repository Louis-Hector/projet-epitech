/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** MaterialFactory
*/

#include "MaterialFactory.hpp"
#include "Dielectric.hpp"
#include "Emissive.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Mirror.hpp"
#include "Transparent.hpp"
#include "RayTracerError.hpp"
#include <memory>

MaterialFactory::MaterialFactory()
{
    builders = {
        {"mat", &MaterialFactory::buildLambertian},
        {"dielectric", &MaterialFactory::buildDielectric},
        {"glass", &MaterialFactory::buildDielectric},
        {"metal", &MaterialFactory::buildMetal},
        {"mirror", &MaterialFactory::buildMirror},
        {"transparent", &MaterialFactory::buildTransparent},
        {"emissive", &MaterialFactory::buildEmissive}
    };
}

static RayTracer::Color getColorFromSetting(libconfig::Setting &setting)
{
    int red = 0;
    int green = 0;
    int blue = 0;

    setting.lookupValue("r", red);
    setting.lookupValue("g", green);
    setting.lookupValue("b", blue);
    return RayTracer::Color(red, green, blue);
}

static RayTracer::Color getOptionalColor(libconfig::Setting &setting, const RayTracer::Color &default_color)
{
    if (!setting.exists("color"))
        return default_color;
    return getColorFromSetting(setting["color"]);
}

static double getOptionalDouble(libconfig::Setting &setting, const char *name, double default_value)
{
    double value = default_value;

    setting.lookupValue(name, value);
    return value;
}

std::unique_ptr<RayTracer::IMaterial> MaterialFactory::createMaterial(libconfig::Setting &setting)
{
    std::string type = "mat";

    setting.lookupValue("type", type);
    const auto element = builders.find(type);
    if (element == builders.end())
        throw FactoryError("Unknown material type: " + type);
    return (this->*(element->second))(setting);
}

std::unique_ptr<RayTracer::IMaterial> MaterialFactory::buildLambertian(libconfig::Setting &setting)
{
    const RayTracer::Color color = getOptionalColor(setting, RayTracer::Color());

    if (setting.exists("transparency") || setting.exists("refraction"))
        return buildDielectric(setting);
    return std::make_unique<RayTracer::Lambertian>(color);
}

std::unique_ptr<RayTracer::IMaterial> MaterialFactory::buildMetal(libconfig::Setting &setting)
{
    const RayTracer::Color color = getOptionalColor(setting, RayTracer::Color(200, 200, 210));
    const double fuzz = getOptionalDouble(setting, "fuzz", 0.0);

    return std::make_unique<RayTracer::Metal>(color, fuzz);
}

std::unique_ptr<RayTracer::IMaterial> MaterialFactory::buildMirror(libconfig::Setting &setting)
{
    const RayTracer::Color color = getOptionalColor(setting, RayTracer::Color(235, 235, 245));

    return std::make_unique<RayTracer::Mirror>(color);
}

std::unique_ptr<RayTracer::IMaterial> MaterialFactory::buildDielectric(libconfig::Setting &setting)
{
    const RayTracer::Color color = getOptionalColor(setting, RayTracer::Color(255, 255, 255));
    const double refraction_index = getOptionalDouble(setting, "refraction", 1.5);
    const double transparency = getOptionalDouble(setting, "transparency", 1.0);

    return std::make_unique<RayTracer::Dielectric>(color, refraction_index, transparency);
}

std::unique_ptr<RayTracer::IMaterial> MaterialFactory::buildTransparent([[maybe_unused]] libconfig::Setting &setting)
{
    return std::make_unique<RayTracer::Transparent>();
}

std::unique_ptr<RayTracer::IMaterial> MaterialFactory::buildEmissive(libconfig::Setting &setting)
{
    const RayTracer::Color color = getOptionalColor(setting, RayTracer::Color(255, 245, 220));
    const double intensity = getOptionalDouble(setting, "intensity", 1.0);

    return std::make_unique<RayTracer::Emissive>(color, intensity);
}
