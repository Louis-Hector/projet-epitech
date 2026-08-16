/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Image
*/

#include "Image.hpp"

namespace RayTracer {

Image::Image(int width, int height) :
    _width(width), _height(height), _pixels(width * height)
{
}

void Image::setPixel(int x, int y, const Color &color)
{
    _pixels[(y * _width) + x] = color;
}

std::vector<Color> Image::getPixels()
{
    return _pixels;
}

const Color &Image::getPixel(int x, int y) const
{
    return _pixels[(y * _width) + x];
}

int Image::getWidth() const
{
    return _width;
}

int Image::getHeight() const
{
    return _height;
}

}
