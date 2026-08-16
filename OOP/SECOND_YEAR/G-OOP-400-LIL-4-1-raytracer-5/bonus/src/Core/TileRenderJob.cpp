/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** TileRenderJob
*/

#include "TileRenderJob.hpp"

namespace RayTracer {

TileRenderJob::TileRenderJob(const RenderContext &context_ref, Image &image_ref, const std::vector<Tile> &tiles_ref, Sfml *sfml_ref) :
    context(context_ref), image(image_ref), tiles(tiles_ref), next_tile(0), completed_tiles(0), sfml(sfml_ref)
{
}

}
