/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <vector>
#include "Color.hpp"

namespace RayTracer {

class Image
{
    private:
        int _width;
        int _height;
        std::vector<Color> _pixels;
    public:
        Image(int width, int height);
        ~Image() = default;

        void setPixel(int x, int y, const Color &color);
        const Color &getPixel(int x, int y) const;
        std::vector<Color> getPixels();
        int getWidth() const;
        int getHeight() const;
};

}

#endif /* !IMAGE_HPP_ */
