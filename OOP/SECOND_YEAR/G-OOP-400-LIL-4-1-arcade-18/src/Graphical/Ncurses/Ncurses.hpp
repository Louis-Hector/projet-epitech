/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IDisplay.hpp"
#include <map>
#include <fstream>
#include <ncurses.h>

class Ncurses : public IDisplay
{
private:
    std::size_t widthWindow = {};
    std::size_t heightWindow = {};
    std::map<std::string, char> _textures;
    std::map<Color, short>_colors;
    WINDOW *window_menu;
    WINDOW *window_game;
public:
    Ncurses(/* args */);
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

#endif /* !NCURSES_HPP_ */

