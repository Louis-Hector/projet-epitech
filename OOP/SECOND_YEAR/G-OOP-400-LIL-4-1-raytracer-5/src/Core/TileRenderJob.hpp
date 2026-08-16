/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** TileRenderJob
*/

#ifndef TILERENDERJOB_HPP_
#define TILERENDERJOB_HPP_

#include <atomic>
#include <cstddef>
#include <mutex>
#include <vector>
#include "RenderContext.hpp"

namespace RayTracer {

class Image;
class Sfml;

struct Tile
{
    int x0;
    int y0;
    int x1;
    int y1;
};

class TileRenderJob
{
    public:
        TileRenderJob(const RenderContext &context, Image &image, const std::vector<Tile> &tiles, Sfml *sfml);
        ~TileRenderJob() = default;

        const RenderContext &context;
        Image &image;
        const std::vector<Tile> &tiles;
        std::atomic<std::size_t> next_tile;
        std::atomic<std::size_t> completed_tiles;
        std::mutex image_mutex;
        Sfml *sfml;
};

}

#endif /* !TILERENDERJOB_HPP_ */
