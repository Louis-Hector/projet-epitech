/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Scene
*/

#include "Scene.hpp"
#include "MathConstants.hpp"

namespace RayTracer {

Scene::Scene() : _camera(), _primitives(), _lights(), _materials(), _unbounded_primitives(), _bvh_root(),
    _ambient_occlusion_enabled(false), _ambient_occlusion_samples(16), _ambient_occlusion_strength(0.5),
    _ambient_occlusion_max_distance(1.5), _samples_per_pixel(100), _max_ray_depth(10), _background_color(127.5, 178.5, 255.0)
{
}

void Scene::addCamera(Camera &camera)
{
    _camera = camera;
}

void Scene::addPrimitive(std::unique_ptr<IPrimitive> primitive)
{
    _primitives.push_back(std::move(primitive));
}

void Scene::addLight(std::unique_ptr<ILight> light)
{
    _lights.push_back(std::move(light));
}

const IMaterial *Scene::addMaterial(std::unique_ptr<IMaterial> material)
{
    _materials.push_back(std::move(material));
    return _materials.back().get();
}

void Scene::buildAccelerationStructure()
{
    std::vector<const IPrimitive *> bounded_primitives;
    AABB box;

    _unbounded_primitives.clear();
    _bvh_root.reset();
    for (const std::unique_ptr<IPrimitive> &primitive : _primitives) {
        if (primitive->boundingBox(box))
            bounded_primitives.push_back(primitive.get());
        else
            _unbounded_primitives.push_back(primitive.get());
    }
    if (!bounded_primitives.empty())
        _bvh_root = std::make_unique<BVHNode>(std::move(bounded_primitives));
}

void Scene::setAmbientOcclusion(bool enabled, int samples, double strength, double max_distance)
{
    _ambient_occlusion_enabled = enabled;
    _ambient_occlusion_samples = samples;
    _ambient_occlusion_strength = strength;
    _ambient_occlusion_max_distance = max_distance;
}

const std::vector<std::unique_ptr<IPrimitive>> &Scene::getPrimitives() const
{
    return _primitives;
}

const std::vector<std::unique_ptr<ILight>> &Scene::getLights() const
{
    return _lights;
}

bool Scene::hitUnboundedPrimitives(const Ray &ray, Intersection &intersection, double max_distance) const
{
    bool found_intersection = false;
    double closest_distance = std::min(intersection.distance, max_distance);

    for (const IPrimitive *primitive : _unbounded_primitives) {
        Intersection current_intersection;

        if (primitive->hit(ray, current_intersection) && current_intersection.distance > EPSILON && current_intersection.distance < closest_distance) {
            intersection = current_intersection;
            closest_distance = current_intersection.distance;
            found_intersection = true;
        }
    }
    return found_intersection;
}

bool Scene::hit(const Ray &ray, Intersection &intersection, double max_distance) const
{
    bool found_intersection = false;

    if (_bvh_root != nullptr)
        found_intersection = _bvh_root->hit(ray, intersection, max_distance);
    if (hitUnboundedPrimitives(ray, intersection, max_distance))
        found_intersection = true;
    return found_intersection;
}

bool Scene::isOccludedWithinDistance(const Ray &ray, double max_distance) const
{
    Intersection intersection;

    return hit(ray, intersection, max_distance);
}

bool Scene::isAmbientOcclusionEnabled() const
{
    return _ambient_occlusion_enabled;
}

int Scene::getAmbientOcclusionSamples() const
{
    return _ambient_occlusion_samples;
}

double Scene::getAmbientOcclusionStrength() const
{
    return _ambient_occlusion_strength;
}

double Scene::getAmbientOcclusionMaxDistance() const
{
    return _ambient_occlusion_max_distance;
}

void Scene::setRenderSettings(int samples_per_pixel, int max_ray_depth, const Color &background_color)
{
    _samples_per_pixel = samples_per_pixel;
    _max_ray_depth = max_ray_depth;
    _background_color = background_color;
}

int Scene::getSamplesPerPixel() const
{
    return _samples_per_pixel;
}

int Scene::getMaxRayDepth() const
{
    return _max_ray_depth;
}

const Color &Scene::getBackgroundColor() const
{
    return _background_color;
}

Camera &Scene::getCamera()
{
    return _camera;
}

}
