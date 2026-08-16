/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <string>
#include <memory>
#include <map>
#include <iostream>
#include <vector>
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "IMaterial.hpp"
#include <libconfig.h++>
#include <vector>
#include "Vector3D.hpp"

class Factory
{
    private:
        using PrimitiveBuilder = std::unique_ptr<RayTracer::IPrimitive>
            (Factory::*)(libconfig::Setting &, const RayTracer::IMaterial *);
    public:
        Factory(/* args */);
        ~Factory() = default;
        std::unique_ptr<RayTracer::IPrimitive> createPrimitive(const std::string &name_element,
            libconfig::Setting &setting, const RayTracer::IMaterial *material);
        std::unique_ptr<RayTracer::ILight> createLight(const std::string &name_element, libconfig::Setting &setting);
        std::vector<double> getValuesDim(libconfig::Setting &setting, const char *name1, const char *name2, const char *name3);
       std::unique_ptr<RayTracer::IPrimitive> buildSphere(libconfig::Setting &setting, const RayTracer::IMaterial *material);
       std::unique_ptr<RayTracer::IPrimitive> buildCylinder(libconfig::Setting &setting, const RayTracer::IMaterial *material);
        std::unique_ptr<RayTracer::IPrimitive> buildLimitedCylinder(libconfig::Setting &setting, const RayTracer::IMaterial *material);
        std::unique_ptr<RayTracer::IPrimitive> buildPlane(libconfig::Setting &setting, const RayTracer::IMaterial *material);
       std::unique_ptr<RayTracer::IPrimitive> buildTriangle(libconfig::Setting &setting, const RayTracer::IMaterial *material);
        std::unique_ptr<RayTracer::IPrimitive> buildPyramid(libconfig::Setting &setting, const RayTracer::IMaterial *material);
       std::unique_ptr<RayTracer::IPrimitive> buildTorus(libconfig::Setting &setting, const RayTracer::IMaterial *material);
       std::unique_ptr<RayTracer::IPrimitive> buildFractal(libconfig::Setting &setting, const RayTracer::IMaterial *material);
       std::unique_ptr<RayTracer::IPrimitive> buildCone(libconfig::Setting &setting, const RayTracer::IMaterial *material);
        std::unique_ptr<RayTracer::IPrimitive> buildLimitedCone(libconfig::Setting &setting, const RayTracer::IMaterial *material);
        std::unique_ptr<RayTracer::IPrimitive> buildMobius(libconfig::Setting &setting, const RayTracer::IMaterial *material);
       std::unique_ptr<RayTracer::IPrimitive> buildTanglecube(libconfig::Setting &setting, const RayTracer::IMaterial *material);
        std::unique_ptr<RayTracer::IPrimitive> buildObj(libconfig::Setting &setting, const RayTracer::IMaterial *material);
        std::map<std::string, PrimitiveBuilder> builders;
};

#endif /* !FACTORY_HPP_ */
