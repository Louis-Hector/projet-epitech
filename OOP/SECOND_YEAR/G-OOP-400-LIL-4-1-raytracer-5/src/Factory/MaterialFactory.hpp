/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** MaterialFactory
*/

#ifndef MATERIALFACTORY_HPP_
#define MATERIALFACTORY_HPP_

#include <map>
#include <memory>
#include <string>
#include <libconfig.h++>
#include "IMaterial.hpp"

class MaterialFactory
{
    private:
        using MaterialPtr = std::unique_ptr<RayTracer::IMaterial>;
        using MaterialSetting = libconfig::Setting;
        using MaterialBuilder = MaterialPtr(MaterialFactory::*)(MaterialSetting &);
    public:
        MaterialFactory();
        ~MaterialFactory() = default;
        std::unique_ptr<RayTracer::IMaterial> createMaterial(libconfig::Setting &setting);
        std::unique_ptr<RayTracer::IMaterial> buildLambertian(libconfig::Setting &setting);
        std::unique_ptr<RayTracer::IMaterial> buildMetal(libconfig::Setting &setting);
        std::unique_ptr<RayTracer::IMaterial> buildMirror(libconfig::Setting &setting);
        std::unique_ptr<RayTracer::IMaterial> buildDielectric(libconfig::Setting &setting);
        std::unique_ptr<RayTracer::IMaterial> buildTransparent(libconfig::Setting &setting);
        std::unique_ptr<RayTracer::IMaterial> buildEmissive(libconfig::Setting &setting);
        std::map<std::string, MaterialBuilder> builders;
};

#endif /* !MATERIALFACTORY_HPP_ */
