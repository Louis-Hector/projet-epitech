#include "Obj.hpp"
#include "Lambertian.hpp"
#include <sstream>
#include <algorithm>

namespace RayTracer {

std::unique_ptr<BVHNode> Obj::buildBVH(std::vector<std::unique_ptr<Triangle>> triangles)
{
    auto node = std::make_unique<BVHNode>();
    Math::Point3D min(BigValue, BigValue, BigValue);
    Math::Point3D max(-BigValue, -BigValue, -BigValue);

    for (const auto& triangle : triangles) {
        std::vector<Math::Point3D> pts = {triangle->getV0(), triangle->getV1(), triangle->getV2()};
        for (const auto& pt : pts) {
            min._x = std::min(min._x, pt._x); min._y = std::min(min._y, pt._y); min._z = std::min(min._z, pt._z);
            max._x = std::max(max._x, pt._x); max._y = std::max(max._y, pt._y); max._z = std::max(max._z, pt._z);
        }
    }
    node->bboxMin = min;
    node->bboxMax = max;

    if (triangles.size() <= 4) {
        node->leafTriangles = std::move(triangles);
        return node;
    }

    double dx = max._x - min._x;
    double dy = max._y - min._y;
    double dz = max._z - min._z;
    int axis = (dx > dy && dx > dz) ? 0 : (dy > dz ? 1 : 2);

    std::sort(triangles.begin(), triangles.end(), [axis](const auto& a, const auto& b) {
        auto center = [](const std::unique_ptr<Triangle>& triangle, int ax) {
            if (ax == 0) return (triangle->getV0()._x + triangle->getV1()._x + triangle->getV2()._x) / 3.0;
            if (ax == 1) return (triangle->getV0()._y + triangle->getV1()._y + triangle->getV2()._y) / 3.0;
            return (triangle->getV0()._z + triangle->getV1()._z + triangle->getV2()._z) / 3.0;
        };
        return center(a, axis) < center(b, axis);
    });

    auto mid = triangles.begin() + triangles.size() / 2;
    std::vector<std::unique_ptr<Triangle>> leftSide, rightSide;
    std::move(triangles.begin(), mid, std::back_inserter(leftSide));
    std::move(mid, triangles.end(), std::back_inserter(rightSide));
    node->left = buildBVH(std::move(leftSide));
    node->right = buildBVH(std::move(rightSide));
    return node;
}

bool Obj::hitSpecificBox(const Math::Point3D& min, const Math::Point3D& max, const Ray& ray) const {
    double tmin = -BigValue;
    double tmax = BigValue;
    
    auto checkAxis = [&](double bmin, double bmax, double r_origin, double r_dir) {
        if (std::abs(r_dir) < 1e-9)
            return r_origin >= bmin && r_origin <= bmax;
        double t1 = (bmin - r_origin) / r_dir;
        double t2 = (bmax - r_origin) / r_dir;
        tmin = std::max(tmin, std::min(t1, t2));
        tmax = std::min(tmax, std::max(t1, t2));
        return true;
    };

    if (!checkAxis(min._x, max._x, ray._origin._x, ray._direction._x))
        return false;
    if (!checkAxis(min._y, max._y, ray._origin._y, ray._direction._y))
        return false;
    if (!checkAxis(min._z, max._z, ray._origin._z, ray._direction._z))
        return false;
    return tmax >= std::max(0.0, tmin);
}

bool Obj::intersectBVH(const BVHNode* node, const Ray &ray, Intersection &inter) const
{
    if (!node || !hitSpecificBox(node->bboxMin, node->bboxMax, ray))
        return false;

    if (node->isLeaf()) {
        bool hit_anything = false;
        double closest = BigValue;
        for (const auto &triangle : node->leafTriangles) {
            Intersection temp;
            if (triangle->hit(ray, temp) && temp.distance < closest) {
                closest = temp.distance;
                inter = temp;
                hit_anything = true;
            }
        }
        return hit_anything;
    }

    Intersection interL, interR;
    bool hitL = intersectBVH(node->left.get(), ray, interL);
    bool hitR = intersectBVH(node->right.get(), ray, interR);

    if (hitL && hitR) {
        if (interL.distance < interR.distance)
            inter = interL;
        else
            inter = interR;
        return true;
    }
    if (hitL) {
        inter = interL;
        return true;
    }else if (hitR) {
        inter = interR;
        return true;
    }
    return false;
}

void Obj::addVertices(std::string line)
{
    std::stringstream ss(line);
    double x, y, z;

    if (ss >> x >> y >> z) {
        double ax = _rotation._x * M_PI / 180.0;
        double ay = _rotation._y * M_PI / 180.0;
        double az = _rotation._z * M_PI / 180.0;
        double ny = y * cos(ax) - z * sin(ax);
        double nz = y * sin(ax) + z * cos(ax);
        y = ny;
        z = nz;

        double nx = x * cos(ay) + z * sin(ay);
        nz = -x * sin(ay) + z * cos(ay);
        x = nx;
        z = nz;
        nx = x * cos(az) - y * sin(az);
        ny = x * sin(az) + y * cos(az);
        x = nx;
        y = ny;

        double finalX = x + _origin._x;
        double finalY = y + _origin._y;
        double finalZ = z + _origin._z;

        _vertices.emplace_back(finalX, finalY, finalZ);
    }
}

void Obj::addFace(const std::string &line, const IMaterial *material)
{
    std::stringstream ss(line);
    std::string block;
    std::vector<int> vertexIndices;

    while (ss >> block) {
        std::stringstream blockStream(block);
        std::string indexStr;

        if (std::getline(blockStream, indexStr, '/')) {
            if (!indexStr.empty()) {
                vertexIndices.push_back(std::stoi(indexStr) - 1);
            }
        }
    }

    for (size_t i = 1; i + 1 < vertexIndices.size(); ++i) {
        int max_size = static_cast<int>(_vertices.size());

        if (vertexIndices[0] < max_size && vertexIndices[i] < max_size && vertexIndices[i+1] < max_size) {
            const Math::Point3D &p1 = _vertices[vertexIndices[0]];
            const Math::Point3D &p2 = _vertices[vertexIndices[i]];
            const Math::Point3D &p3 = _vertices[vertexIndices[i + 1]];

            _triangles.push_back(std::make_unique<RayTracer::Triangle>(p1, p2, p3, material));
        }
    }
}

void Obj::parseMtl(const std::filesystem::path& mtlPath)
{
    std::ifstream mtlFile(mtlPath);
    if (!mtlFile.is_open())
        return;

    std::string line;
    std::string currentMatName;
    while (std::getline(mtlFile, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "newmtl") {
            ss >> currentMatName;
        } else if (prefix == "Kd" && !currentMatName.empty()) {
            double r, g, b;
            if (ss >> r >> g >> b) {
                Color matColor(static_cast<int>(r * 255), static_cast<int>(g * 255), static_cast<int>(b * 255));
                _materials[currentMatName] = std::make_unique<Lambertian>(matColor);
            }
        }
    }
}

Obj::Obj(std::string path, Math::Point3D origin, Math::Vector3D rotation)
    : _origin(origin), _rotation(rotation)
{
    std::filesystem::path dirPath(path);
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath)) {
        throw std::runtime_error("wrong path : " + path);
    }

    std::filesystem::path objPath = dirPath / "model.obj";
    std::filesystem::path mtlPath = dirPath / "materials.mtl";

    parseMtl(mtlPath);

    std::ifstream objFile(objPath);
    if (!objFile.is_open()) {
        throw std::runtime_error("can't open file " + objPath.string());
    }

    std::string line;
    const IMaterial *currentMaterial = nullptr;

    while (std::getline(objFile, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            addVertices(line.substr(line.find_first_of("v") + 1));
        }
        else if (prefix == "usemtl") {
            std::string matName;
            ss >> matName;
            if (_materials.count(matName)) {
                currentMaterial = _materials[matName].get();
            }
        }
        else if (prefix == "f") {
            addFace(line.substr(line.find_first_of("f") + 1), currentMaterial);
        }
    }
    _root = buildBVH(std::move(_triangles));
}

bool Obj::hit(const Ray &ray, Intersection &inter) const
{
    if (!_root)
            return false;
    return intersectBVH(_root.get(), ray, inter);
}

bool Obj::boundingBox(AABB &box) const
{
    box = AABB(_bboxMin, _bboxMax);
    return true;
}

Obj::~Obj() {}

}
