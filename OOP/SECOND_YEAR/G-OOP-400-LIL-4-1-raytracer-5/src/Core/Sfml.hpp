/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "Color.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
constexpr int SPEED = 20;
constexpr double OFFSET_MOVEMENT = 1.0;
constexpr double OFFSET_ROTATION = 15.0;
class Sfml {
    public:
        Sfml(Camera &camera);
        ~Sfml();
        void drawImage(std::vector<Color> pixels);
        int updateAndShow(const std::vector<Color>& pixels);
        int handleKey(sf::Event event);
        bool isOpen() const;
        int handleEvent();
    private:
        Camera &_camera;
        int _width;
        int _height;
        sf::RenderWindow _window;
        sf::Texture _texture;
        sf::Sprite _sprite;
        std::vector<sf::Uint8> _pixelsBuffer;
};
}

#endif /* !SFML_HPP_ */
