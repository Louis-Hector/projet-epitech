/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** IGame
*/

#ifndef IGame_HPP_
    #define IGame_HPP_

#include "ALib.hpp"
#include "IDisplay.hpp"

struct Texte {
    int x = 0;
    int y = 0;
    float size = 1.0f;
    std::string text = "";
    Color color = WHITE;
};

struct Sprite {
    int x = 0;
    int y = 0;
    int rotation = 0;
    float size = 1.0f;
    std::string name = "";
};

class IGame : public ALib {
    public:
        virtual ~IGame() = default;
        virtual void update(InputEvent key) = 0;
        virtual bool isOver() = 0;
        virtual std::size_t getScore() = 0;
        virtual std::vector<Sprite> getSprites() = 0;
        virtual std::vector<Texte> getTextes() = 0;
        virtual std::vector<std::string> getSounds() = 0;
    protected:
        std::vector<Sprite> _sprites;
        std::vector<Texte> _texts;
        std::vector<std::string> _sounds;
        std::size_t _score = 0;
};

#endif /* !IGame_HPP_ */
