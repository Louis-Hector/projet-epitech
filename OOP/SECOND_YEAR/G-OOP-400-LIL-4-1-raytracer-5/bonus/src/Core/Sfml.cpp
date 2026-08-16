/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sfml
*/

#include "Sfml.hpp"
#include <cmath>

namespace RayTracer {

    static sf::Uint8 to_display_channel(double linear_component)
    {
        const double normalized = std::clamp(linear_component / 255.0, 0.0, 1.0);
        const double gamma_corrected = std::sqrt(normalized);

        return static_cast<sf::Uint8>(255.999 * gamma_corrected);
    }

    Sfml::Sfml(Camera &camera) : _camera(camera), _width(camera.getWidth()), _height(camera.getHeight()),
        _window(sf::VideoMode({(unsigned int)_width, (unsigned int)_height}), "Raytracer")
    {
        _texture.create(_width, _height);
        _sprite.setTexture(_texture);
        _pixelsBuffer.resize(_width * _height * 4);
    }

    Sfml::~Sfml()
    {
    }

    bool Sfml::isOpen() const
    {
        return _window.isOpen();
    }

    void Sfml::drawImage(std::vector<Color> pixels)
    {
        for (size_t i = 0; i < pixels.size(); i++) {
            const Color mapped = pixels[i].clamped();

            _pixelsBuffer[i * 4] = to_display_channel(mapped._r);
            _pixelsBuffer[i * 4 + 1] = to_display_channel(mapped._g);
            _pixelsBuffer[i * 4 + 2] = to_display_channel(mapped._b);
            _pixelsBuffer[i * 4 + 3] = 255;
        }

        _texture.update(_pixelsBuffer.data());
        _window.draw(_sprite);
        _window.display();
    }

    int Sfml::handleKey(sf::Event event)
    {
        if (event.key.code == sf::Keyboard::Right) {
            _camera.rotateCamera({0.0, -OFFSET_ROTATION, 0.0 });
            return 1;
        }
        if (event.key.code == sf::Keyboard::Left) {
            _camera.rotateCamera({0.0, OFFSET_ROTATION, 0.0 });
            return 1;
        }
        if (event.key.code == sf::Keyboard::Up) {
            _camera.rotateCamera({OFFSET_ROTATION, 0.0, 0.0 });
            return 1;
        }
        if (event.key.code == sf::Keyboard::Down) {
            _camera.rotateCamera({-OFFSET_ROTATION, 0.0, 0.0 });
            return 1;
        }
        if (event.key.code == sf::Keyboard::Z) {
            _camera.moveCamera({0.0, 0.0, OFFSET_MOVEMENT });
            return 1;
        }
        if (event.key.code == sf::Keyboard::Q) {
            _camera.moveCamera({OFFSET_MOVEMENT, 0.0, 0.0 });
            return 1;
        }
        if (event.key.code == sf::Keyboard::S) {
            _camera.moveCamera({0.0, 0.0, -OFFSET_MOVEMENT });
            return 1;
        }
        if (event.key.code == sf::Keyboard::D) {
            _camera.moveCamera({-OFFSET_MOVEMENT, 0.0, 0.0 });
            return 1;
        }
        return 0;
    }

    int Sfml::updateAndShow(const std::vector<Color>& pixels)
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                _window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (handleKey(event))
                    return 1;
            }
        }
        drawImage(pixels);
        return 0;
    }
}
