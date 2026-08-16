/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** main
*/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "PpmWriter.hpp"
#include "RayTracerError.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Parsing.hpp"
#include "Sfml.hpp"
#include <libconfig.h++>

struct Flags
{
    bool render_sfml = false;
    bool show_help = false;
    std::string scene_file;
};

static void print_help()
{
    std::cout << "USAGE: ./raytracer [SCENE_FILE] [-s]" << '\n';
    std::cout << "  SCENE_FILE: scene configuration" << '\n';
    std::cout << "Without SCENE_FILE, every scene in scenes/ is rendered to screenshots/.\n";
    std::cout << "Flags:\n" << "  --sfml : show runtime SFML rendering" << std::endl;
}

static Flags parse_args(int ac, char **av)
{
    Flags options;

    if (ac > 3)
        throw ParsingError("Invalid number of args");
    for (int i = 1; i < ac; i++) {
        const std::string argument = av[i];

        if (argument == "--help") {
            if (options.show_help)
                throw ParsingError("Duplicate --help argument");
            options.show_help = true;
            continue;
        }
        if (argument == "--sfml") {
            if (options.render_sfml)
                throw ParsingError("Duplicate --sfml argument");
            options.render_sfml = true;
            continue;
        }
        if (!options.scene_file.empty())
            throw ParsingError("Invalid number of scene files");
        options.scene_file = argument;
    }
    return options;
}

static RayTracer::Image render_scene(RayTracer::Scene &scene, bool render_sfml)
{
    const RayTracer::Renderer renderer;

    if (!render_sfml)
        return renderer.render(scene, scene.getCamera());
    RayTracer::Sfml sfml(scene.getCamera());
    RayTracer::Image image = renderer.render(scene, scene.getCamera(), sfml);

    while (sfml.isOpen()) {
        if (sfml.updateAndShow(image.getPixels()))
            image = renderer.render(scene, scene.getCamera(), sfml);
    }
    return image;
}

static void render_file(Parsing &parse, const std::string &scene_file, std::ostream &output, Flags &options)
{
    const RayTracer::PpmWriter ppm_writer;
    RayTracer::Scene scene;

    parse.open_file(scene_file.c_str(), scene);
    if (&output == &std::cout) {
        std::string name_file = std::filesystem::path(scene_file).stem().string();
        std::string path_file = "screenshots/" + name_file + ".ppm";
        std::ofstream file(path_file);
        std::cout << "File " << scene_file << " is being processed to " << path_file << std::endl;
        ppm_writer.write(render_scene(scene, options.render_sfml), file);
    } else
        ppm_writer.write(render_scene(scene, options.render_sfml), output);
}

static void render_all_files(Parsing &parse, Flags &options)
{
    std::filesystem::create_directories("screenshots");
    for (const auto &entry : std::filesystem::directory_iterator("scenes")) {
        if (entry.is_directory() || !entry.is_regular_file())
            continue;
        auto file = entry.path().string();
        auto pos_exten = file.find_last_of('.');
        if (pos_exten == std::string::npos || file.substr(pos_exten + 1) != "cfg")
            continue;
        auto file_name = entry.path().stem().string();
        std::string dest = "screenshots/" + file_name + ".ppm";
        std::cout << "File " << entry.path().string() << " is being processed to " << dest << "." << std::endl;
        std::ofstream file_output(dest);

        if (!file_output.is_open())
            throw ParsingError("Could not open output file: " + dest);
        render_file(parse, entry.path().string(), file_output, options);
    }
}

static void run_raytracer(Flags &options)
{
    Parsing parse;
    if (options.scene_file.empty()) {
        render_all_files(parse, options);
        return;
    }
    render_file(parse, options.scene_file, std::cout, options);
}

int main(int ac, char **av)
{
    try {
        Flags options = parse_args(ac, av);

        if (options.show_help) {
            print_help();
            return 0;
        }
        run_raytracer(options);
    } catch (const libconfig::SettingException &error) {
        std::cerr << error.what() << ": " << error.getPath() << '\n';
        return 84;
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 84;
    }
    return 0;
}
