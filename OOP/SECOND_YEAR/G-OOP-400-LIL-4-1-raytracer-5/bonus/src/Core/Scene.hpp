/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <memory>
#include <vector>
#include "BVHNode.hpp"
#include "Color.hpp"
#include "ILight.hpp"
#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "Camera.hpp"

namespace RayTracer {

class Scene
{
    private:
        Camera _camera;
        std::vector<std::unique_ptr<IPrimitive>> _primitives;
        std::vector<std::unique_ptr<ILight>> _lights;
        std::vector<std::unique_ptr<IMaterial>> _materials;
        std::vector<const IPrimitive *> _unbounded_primitives;
        std::unique_ptr<BVHNode> _bvh_root;
        bool _ambient_occlusion_enabled;
        int _ambient_occlusion_samples;
        double _ambient_occlusion_strength;
        double _ambient_occlusion_max_distance;
        int _samples_per_pixel;
        int _max_ray_depth;
        Color _background_color;

        bool hitUnboundedPrimitives(const Ray &ray, Intersection &intersection, double max_distance) const;
    public:
        Scene();
        ~Scene() = default;

        void addCamera(Camera &camera);
        void addPrimitive(std::unique_ptr<IPrimitive> primitive);
        void addLight(std::unique_ptr<ILight> light);
        const IMaterial *addMaterial(std::unique_ptr<IMaterial> material);
        void buildAccelerationStructure();
        void setAmbientOcclusion(bool enabled, int samples, double strength, double max_distance);
        const std::vector<std::unique_ptr<IPrimitive>> &getPrimitives() const;
        const std::vector<std::unique_ptr<ILight>> &getLights() const;
        bool hit(const Ray &ray, Intersection &intersection, double max_distance) const;
        bool isOccludedWithinDistance(const Ray &ray, double max_distance) const;
        bool isAmbientOcclusionEnabled() const;
        int getAmbientOcclusionSamples() const;
        double getAmbientOcclusionStrength() const;
        double getAmbientOcclusionMaxDistance() const;
        void setRenderSettings(int samples_per_pixel, int max_ray_depth, const Color &background_color);
        int getSamplesPerPixel() const;
        int getMaxRayDepth() const;
        const Color &getBackgroundColor() const;
        Camera &getCamera();
        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene(Scene&&) = default;
        Scene& operator=(Scene&&) = default;
};

}

#endif /* !SCENE_HPP_ */
