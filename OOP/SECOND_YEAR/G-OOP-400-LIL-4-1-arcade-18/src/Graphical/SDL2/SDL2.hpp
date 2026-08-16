/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Sdl2
*/

#ifndef SDL2_HPP_
#define SDL2_HPP_

#include "IDisplay.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <map>

class Sdl2 : public IDisplay
{
    private:
        TTF_Font *_font = nullptr; 
        Mix_Music *_music = nullptr;
        SDL_Renderer *_render = nullptr;
        SDL_Window *_window = nullptr;
        std::map<Color, SDL_Color> _colors;
        std::map<std::string, SDL_Texture *> _textures;
        std::map<std::string, Mix_Chunk *> _sounds;
    protected:
    public:
        Sdl2(/* args */);
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

#endif /* !SDL2_HPP_ */
