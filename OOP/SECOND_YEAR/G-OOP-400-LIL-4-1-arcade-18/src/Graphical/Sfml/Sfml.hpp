/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IDisplay.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <map>

class Sfml : public IDisplay
{
private:
    sf::RenderWindow _window; 
    sf::Font *_font; 
    std::map<Color, sf::Color> _colors;
    std::map<std::string, sf::Texture> _textures;
    std::map<std::string, sf::SoundBuffer> _sounds;
    std::vector<sf::Sound> _playsound;

public:
    Sfml();
    int createWindow() override;
    void closeWindow() override;
    void clear() override;
    void display() override;
    InputEvent getInput() override;
    void drawBackground(std::string background_name) override;
    void drawText(pos position, float size, std::string text, Color color) override;
    void drawSprite(pos position, int rotation, float size, std::string name) override;
    std::string loadName() override;
    int loadTexture(std::string game) override;
    int loadSound(std::string game) override;
    int playSound(std::string sound_name_in_map) override;
    std::tuple<int, int> recoverWindowSize() override;
};

#endif /* !SFML_HPP_ */
