/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ObjParser
*/

#ifndef OBJ_HPP_
#define OBJ_HPP_
#include <iostream>
#include <vector>
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Color.hpp"
#include <tuple>
#include "IPrimitive.hpp"
#include <fstream>
#include <filesystem>
#include "Triangle.hpp"
#include <map>
#include "Lambertian.hpp"
#include <cmath>

namespace RayTracer {

constexpr double BigValue = 1e30;

struct BVHNode {
    Math::Point3D bboxMin, bboxMax;
    std::unique_ptr<BVHNode> left;
    std::unique_ptr<BVHNode> right;
    std::vector<std::unique_ptr<Triangle>> leafTriangles; 

    bool isLeaf() const { 
        return left == nullptr && right == nullptr; 
    };
};

class Obj: public IPrimitive {
    private:
        std::vector<Math::Point3D> _vertices;
        std::unique_ptr<BVHNode> _root;
        std::vector<std::unique_ptr<Triangle>> _triangles;
        std::map<std::string, std::unique_ptr<IMaterial>> _materials;
        Math::Point3D _origin;
        Math::Vector3D _rotation;
        Math::Point3D _bboxMin;
        Math::Point3D _bboxMax;

        void addVertices(std::string line);
        void addFace(const std::string &line, const IMaterial *currentMat);
        void parseMtl(const std::filesystem::path& mtlPath);
        bool testAxis(double min, double max, double origin, double direction);
        bool intersectBVH(const BVHNode* node, const Ray &ray, Intersection &inter) const;
        bool hitSpecificBox(const Math::Point3D& min, const Math::Point3D& max, const Ray& ray) const;
        std::unique_ptr<BVHNode> buildBVH(std::vector<std::unique_ptr<Triangle>> triangles);
    public:
        Obj(std::string path, Math::Point3D origin, Math::Vector3D rotation = {0, 0, 0});
        ~Obj();
        bool hit(const Ray &ray, Intersection &inter) const override;
        bool boundingBox(AABB &box) const override;
    };
}

#endif
