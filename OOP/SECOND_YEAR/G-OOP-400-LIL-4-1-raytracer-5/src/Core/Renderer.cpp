/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "MathUtils.hpp"
#include "MathConstants.hpp"
#include "Sfml.hpp"
#include "SpotLight.hpp"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <mutex>
#include <thread>
#include <vector>

namespace RayTracer {

std::vector<Tile> Renderer::buildTiles(int width, int height) const
{
    std::vector<Tile> tiles;

    for (int y = 0; y < height; y += TILE_SIZE) {
        for (int x = 0; x < width; x += TILE_SIZE) {
            tiles.push_back({x, y, std::min(x + TILE_SIZE, width), std::min(y + TILE_SIZE, height)});
        }
    }
    return tiles;
}

static Color computeShadowTransmission(const Scene &scene, const Ray &shadow_ray, double max_distance, int max_ray_depth)
{
    Color transmission(255.0, 255.0, 255.0);
    Ray current_ray = shadow_ray;
    double remaining_distance = max_distance;
    int interaction_count = 0;

    while (interaction_count < max_ray_depth) {
        Intersection nearest_intersection;

        if (!scene.hit(current_ray, nearest_intersection, remaining_distance - EPSILON))
            return transmission;
        if (nearest_intersection.material == nullptr || !nearest_intersection.material->transmitsLight())
            return Color();
        Color material_transmission;
        Ray scattered_shadow_ray;

        if (!nearest_intersection.material->scatterShadowRay(current_ray, nearest_intersection, material_transmission, scattered_shadow_ray)) {
            return Color();
        }
        transmission = transmission * material_transmission;
        if (transmission._r <= 0.0 && transmission._g <= 0.0 && transmission._b <= 0.0)
            return Color();
        remaining_distance -= nearest_intersection.distance;
        if (remaining_distance <= EPSILON)
            return transmission;
        current_ray = scattered_shadow_ray;
        interaction_count++;
    }
    return Color();
}

static bool isInsideSpotCone(const ILight &light, const Intersection &intersection)
{
    const SpotLight *spot_light = dynamic_cast<const SpotLight *>(&light);

    if (spot_light == nullptr)
        return true;
    const Math::Vector3D spot_axis = Math::normalize(spot_light->getAxisDirection());
    const Math::Vector3D light_to_point = Math::normalize(intersection.position - spot_light->getPosition());
    const double cutoff_cosine = std::cos(spot_light->getAngle() * M_PI / 180.0);

    return spot_axis.dot(light_to_point) >= cutoff_cosine;
}

static Math::Vector3D randomCosineHemisphereDirection(const Math::Vector3D &normal)
{
    const Math::Vector3D w = Math::normalize(normal);
    const Math::Vector3D helper = (std::fabs(w._x) > 0.9) ? Math::Vector3D(0.0, 1.0, 0.0) : Math::Vector3D(1.0, 0.0, 0.0);
    const Math::Vector3D v = Math::normalize(w.cross(helper));
    const Math::Vector3D u = v.cross(w);
    const double r1 = Math::randomDouble();
    const double r2 = Math::randomDouble();
    const double phi = 2.0 * M_PI * r1;
    const double radius = std::sqrt(r2);
    const double x = std::cos(phi) * radius;
    const double y = std::sin(phi) * radius;
    const double z = std::sqrt(1.0 - r2);
    return Math::normalize(u * x + v * y + w * z);
}

static double computeAmbientOcclusion(const Scene &scene, const Intersection &intersection)
{
    if (!scene.isAmbientOcclusionEnabled())
        return 1.0;
    int unoccluded_samples = 0;

    for (int sample = 0; sample < scene.getAmbientOcclusionSamples(); sample++) {
        const Math::Vector3D sample_direction = randomCosineHemisphereDirection(intersection.surface_normal);
        const Ray occlusion_ray(intersection.position + intersection.surface_normal * EPSILON, sample_direction);

        if (!scene.isOccludedWithinDistance(occlusion_ray, scene.getAmbientOcclusionMaxDistance()))
            unoccluded_samples++;
    }
    const double visibility = static_cast<double>(unoccluded_samples) / scene.getAmbientOcclusionSamples();
    return (1.0 - scene.getAmbientOcclusionStrength()) + scene.getAmbientOcclusionStrength() * visibility;
}

RenderConfig Renderer::buildRenderConfig(const Scene &scene) const
{
    return {scene.getSamplesPerPixel(), scene.getMaxRayDepth(), scene.getBackgroundColor()};
}

Color Renderer::background(const Ray &ray, const RenderContext &context) const
{
    const Math::Vector3D unit_direction = Math::normalize(ray._direction);
    const double t = 0.5 * (unit_direction._y + 1.0);

    return Color(255.0, 255.0, 255.0) * (1.0 - t) + context.config.background_color * t;
}

Color Renderer::sampleDirectLighting(const RenderContext &context, const Intersection &intersection) const
{
    if (intersection.material == nullptr || intersection.material->isDelta())
        return Color();
    const Color albedo = intersection.material->getAlbedo();
    Color direct_lighting;

    for (const std::unique_ptr<ILight> &light : context.scene.getLights()) {
        const Math::Vector3D light_direction = Math::normalize(light->getDirectionFrom(intersection.position));
        const double diffuse_strength = std::max(0.0, intersection.surface_normal.dot(light_direction));
        const double light_distance = light->getDistanceFrom(intersection.position);
        const Ray shadow_ray(intersection.position + intersection.surface_normal * EPSILON, light_direction);
        const Color shadow_transmission = computeShadowTransmission(context.scene, shadow_ray, light_distance, context.config.max_ray_depth);
        double attenuation = 1.0;

        if (diffuse_strength <= 0.0 || !isInsideSpotCone(*light, intersection))
            continue;
        if (shadow_transmission._r <= 0.0 && shadow_transmission._g <= 0.0 && shadow_transmission._b <= 0.0)
            continue;
        if (std::isfinite(light_distance)) {
            attenuation = 1.0 / (LIGHT_ATTENUATION_CONSTANT + LIGHT_ATTENUATION_LINEAR * light_distance +
                LIGHT_ATTENUATION_QUADRATIC * light_distance * light_distance);
        }
        direct_lighting += ((albedo * light->getColor()) * shadow_transmission) *
            (light->getIntensity() * diffuse_strength * attenuation);
    }
    return direct_lighting;
}

Color Renderer::traceRay(const RenderContext &context, const Ray &ray, int depth) const
{
    if (depth <= 0)
        return Color();
    Intersection hit;

    if (!context.scene.hit(ray, hit, hit.distance))
        return background(ray, context);
    if (hit.material == nullptr)
        return Color();
    const Color emitted = hit.material->emit();
    const Color direct_lighting = sampleDirectLighting(context, hit);
    const double ambient_occlusion = (hit.material->isDelta()) ? 1.0 : computeAmbientOcclusion(context.scene, hit);
    Ray scattered;
    Color attenuation;

    if (!hit.material->scatter(ray, hit, attenuation, scattered))
        return emitted + direct_lighting;
    return emitted + (direct_lighting + attenuation * traceRay(context, scattered, depth - 1)) * ambient_occlusion;
}

Color Renderer::getPixelColor(const RenderContext &context, int x, int y) const
{
    Color pixel_color;

    for (int sample = 0; sample < context.config.samples_per_pixel; sample++) {
        double u = static_cast<double>(x + Math::randomDouble()) / (context.camera.getWidth() - 1);
        double v = static_cast<double>(y + Math::randomDouble()) / (context.camera.getHeight() - 1);
        Ray ray = context.camera.ray(u, v);
        pixel_color += traceRay(context, ray, context.config.max_ray_depth);
    }
    return pixel_color * (1.0 / context.config.samples_per_pixel);
}

void Renderer::renderTile(TileRenderJob &job, const Tile &tile) const
{
    std::vector<Color> tile_pixels((tile.x1 - tile.x0) * (tile.y1 - tile.y0));
    std::size_t index = 0;

    for (int y = tile.y0; y < tile.y1; y++) {
        for (int x = tile.x0; x < tile.x1; x++) {
            tile_pixels[index] = getPixelColor(job.context, x, y);
            index++;
        }
    }
    std::lock_guard<std::mutex> lock(job.image_mutex);
    index = 0;
    for (int y = tile.y0; y < tile.y1; y++) {
        for (int x = tile.x0; x < tile.x1; x++) {
            job.image.setPixel(x, y, tile_pixels[index]);
            index++;
        }
    }
}

void Renderer::renderTileBatch(TileRenderJob &job) const
{
    while (true) {
        const std::size_t tile_index = job.next_tile.fetch_add(1);

        if (tile_index >= job.tiles.size())
            break;
        renderTile(job, job.tiles[tile_index]);
        job.completed_tiles.fetch_add(1);
    }
}

void Renderer::refreshSfmlPreview(TileRenderJob &job) const
{
    while (job.completed_tiles.load() < job.tiles.size()) {
        if (job.sfml != nullptr && job.sfml->isOpen()) {
            job.sfml->handleEvent();
            std::lock_guard<std::mutex> lock(job.image_mutex);
            job.sfml->drawImage(job.image.getPixels());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

Image Renderer::render(const Scene &scene, const Camera &camera, Sfml &sfml) const
{
    return renderTiled(scene, camera, &sfml, buildRenderConfig(scene));
}

Image Renderer::render(const Scene &scene, const Camera &camera) const
{
    return renderTiled(scene, camera, nullptr, buildRenderConfig(scene));
}

Image Renderer::renderTiled(const Scene &scene, const Camera &camera, Sfml *sfml, const RenderConfig &config) const
{
    Image image(camera.getWidth(), camera.getHeight());
    const std::vector<Tile> tiles = buildTiles(camera.getWidth(), camera.getHeight());
    const RenderContext context{scene, camera, config};
    TileRenderJob job(context, image, tiles, sfml);
    const std::size_t thread_count = std::max<std::size_t>(1, std::thread::hardware_concurrency());
    std::vector<std::thread> workers;

    workers.reserve(thread_count);
    for (std::size_t worker_index = 0; worker_index < thread_count; worker_index++)
        workers.emplace_back(&Renderer::renderTileBatch, this, std::ref(job));
    refreshSfmlPreview(job);
    for (std::thread &worker : workers) {
        if (worker.joinable())
            worker.join();
    }
    if (job.sfml != nullptr && job.sfml->isOpen()) {
        std::lock_guard<std::mutex> lock(job.image_mutex);
        job.sfml->drawImage(job.image.getPixels());
    }
    return image;
}
}
