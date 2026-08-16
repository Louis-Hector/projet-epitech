/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Parsing
*/

#include "Parsing.hpp"
#include "MathConstants.hpp"
#include <algorithm>

Parsing::Parsing(/* args */)
{
}

Parsing::~Parsing()
{
}

void Parsing::parseLights(libconfig::Setting &root, RayBuilder &builder_scene)
{
    if (!root.exists("lights"))
        return;
    libconfig::Setting &info_lights = root["lights"];
    if (info_lights.exists("directional")) {
        libconfig::Setting &directional = info_lights["directional"];
        for (int i = 0; i < directional.getLength(); i++)
            builder_scene.appendLight("directional", directional[i]);
    }
    if (info_lights.exists("point")) {
        libconfig::Setting &point = info_lights["point"];
        for (int i = 0; i < point.getLength(); i++)
            builder_scene.appendLight("point", point[i]);
    }
    if (info_lights.exists("spot")) {
        libconfig::Setting &spot = info_lights["spot"];
        for (int i = 0; i < spot.getLength(); i++)
            builder_scene.appendLight("spot", spot[i]);
    }
}

static void parseAmbientOcclusion(libconfig::Setting &root, RayTracer::Scene &scene)
{
    if (!root.exists("ambientOcclusion"))
        return;
    libconfig::Setting &ambient_occlusion = root["ambientOcclusion"];
    bool enabled = true;
    int samples = 16;
    double strength = 0.5;
    double max_distance = 1.5;

    ambient_occlusion.lookupValue("enabled", enabled);
    ambient_occlusion.lookupValue("samples", samples);
    ambient_occlusion.lookupValue("strength", strength);
    ambient_occlusion.lookupValue("maxDistance", max_distance);
    scene.setAmbientOcclusion(enabled, std::max(samples, 1), std::clamp(strength, 0.0, 1.0), std::max(max_distance, RayTracer::EPSILON));
}

void Parsing::create_scene(RayBuilder &builder_scene, libconfig::Setting &root)
{
    if (root.exists("materials")) {
        libconfig::Setting &materials = root["materials"];
        for (int i = 0; i < materials.getLength(); i++)
            builder_scene.appendMaterial(materials[i]);
    }
    libconfig::Setting &primitives = root["primitives"];
    for (int i = 0; i < primitives.getLength(); i++) {
        libconfig::Setting &shape = primitives[i];
        for (int j = 0; j < shape.getLength(); j++)
            builder_scene.appendPrimitive(shape.getName(), shape[j]);
    }
    parseLights(root, builder_scene);
}

void Parsing::import_new_file(RayBuilder &builder, const char *file_name)
{
    libconfig::Config conf;
    std::ifstream file(file_name);
    RayBuilder builder_scene;

    try {
        conf.readFile(file_name);
    }
    catch(const libconfig::FileIOException &fioex) {
        throw ParsingError("An error occurred while reading the file");
    } catch(const libconfig::ParseException &pex) {
        throw ParsingError("Error detected in the file: " + std::string(pex.getFile()) + " on the line : " + std::to_string(pex.getLine()));
    }
    libconfig::Setting &root = conf.getRoot();
    create_scene(builder, root);
    return;
}

void Parsing::open_file(const char *file_name, RayTracer::Scene &scene)
{
    libconfig::Config conf;
    std::ifstream file(file_name);
    RayBuilder builder_scene;

    try {
        conf.readFile(file_name);
    }
    catch(const libconfig::FileIOException &fioex) {
        throw ParsingError("An error occurred while reading the file");
    } catch(const libconfig::ParseException &pex) {
        throw ParsingError("Error detected in the file: " + std::string(pex.getFile()) + " on the line : " + std::to_string(pex.getLine()));
    }
    libconfig::Setting &root = conf.getRoot();
    if (root.getLength() == 0)
        throw ParsingError("The file does not contain any setting");
    libconfig::Setting &camera = root["camera"];
    if (camera.getLength() == 0)
        throw ParsingError("The file has not defined the camera");
    builder_scene.appendCamera(camera);
    if (root.exists("settings"))
        builder_scene.appendSettings(root["settings"]);
    if (root.exists("materials")) {
        libconfig::Setting &materials = root["materials"];

        for (int i = 0; i < materials.getLength(); i++)
            builder_scene.appendMaterial(materials[i]);
    }
    create_scene(builder_scene, root);
    if (root.exists("import")) {
        libconfig::Setting &import = root["import"];
        for (int i = 0; i < import. getLength(); i++) {
            for (int j = 0; j < import[i].getLength(); j++) {
                std::string name_file;
                import[i][j].lookupValue("name", name_file);
                import_new_file(builder_scene, (name_file).c_str());
            }
        }
    }
    scene = builder_scene.build();
    parseAmbientOcclusion(root, scene);
    scene.buildAccelerationStructure();
    return;
}
