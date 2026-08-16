/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <libconfig.h++>
#include "Builder.hpp"
#include "RayTracerError.hpp"

class Parsing
{
private:
    void parseLights(libconfig::Setting &root, RayBuilder &builder_scene);
public:
    Parsing(/* args */);
    ~Parsing();
    void create_scene(RayBuilder &builder_scene, libconfig::Setting &root);
    void import_new_file(RayBuilder &builder, const char *file_name);
    void open_file(const char *file_name, RayTracer::Scene &scene);
};

#endif /* !PARSING_HPP_ */
