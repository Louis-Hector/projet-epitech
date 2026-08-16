/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "Camera.hpp"
#include "Image.hpp"
#include "RenderContext.hpp"
#include "RenderConfig.hpp"
#include "TileRenderJob.hpp"
#include "Scene.hpp"
#include "Sfml.hpp"
#include <vector>

namespace RayTracer {

static constexpr int TILE_SIZE = 32;
static constexpr double LIGHT_ATTENUATION_CONSTANT = 1.0;
static constexpr double LIGHT_ATTENUATION_LINEAR = 0.1;
static constexpr double LIGHT_ATTENUATION_QUADRATIC = 0.03;

class Renderer
{
    private:
        std::vector<Tile> buildTiles(int width, int height) const;
        RenderConfig buildRenderConfig(const Scene &scene, bool preview_mode) const;
        Color getPixelColor(const RenderContext &context, int x, int y) const;
        Color traceRay(const RenderContext &context, const Ray &ray, int depth) const;
        Color background(const Ray &ray, const RenderContext &context) const;
        Color sampleDirectLighting(const RenderContext &context, const Intersection &intersection) const;
        void renderTile(TileRenderJob &job, const Tile &tile) const;
        void renderTileBatch(TileRenderJob &job) const;
        void refreshSfmlPreview(TileRenderJob &job) const;
        Image renderTiled(const Scene &scene, const Camera &camera, Sfml *sfml, const RenderConfig &config, const Image *initial_image = nullptr) const;
    public:
        Renderer() = default;
        ~Renderer() = default;

        Image render(const Scene &scene, const Camera &camera, Sfml &sfml) const;
        Image render(const Scene &scene, const Camera &camera) const;
};

}

#endif /* !RENDERER_HPP_ */
