/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
    #define IDISPLAY_HPP_
#define FONT_PATH "assets/font/Nasa21.ttf"

#include "ALib.hpp"

struct pos {
    int x;
    int y;
};

enum EventType {
    UP_ARROW,
    DOWN_ARROW,
    LEFT_ARROW,
    RIGHT_ARROW,
    LEFT_CLICK,
    RIGHT_CLICK,
    SWITCH_DISPLAY,
    SWITCH_GAME,
    RESTART_GAME,
    CALL_MENU,
    ENTER,
    SPACE,
    QUIT,
    ROAR,
    UNKNOWN
};

enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    WHITE,
    MAGENTA,
    CYAN
};

struct InputEvent {
    EventType event = EventType::UNKNOWN;
    pos mouse = {0, 0};
};

class IDisplay : public ALib {
    private:
    protected:
    public:
        virtual ~IDisplay() = default;
        virtual int createWindow() = 0;
        virtual void closeWindow() = 0;
        virtual void clear() = 0;
        virtual void display() = 0;
        virtual InputEvent getInput() = 0;
        virtual void drawBackground(std::string background_name) = 0;
        virtual void drawText(pos position, float size, std::string text, Color color) = 0;
        virtual void drawSprite(pos position, int rotation, float size, std::string name) = 0;
        virtual int loadTexture(std::string game) = 0;
        virtual int loadSound(std::string game) = 0;
        virtual int playSound(std::string sound_name_in_map) = 0;
        virtual std::string loadName() = 0;
        virtual std::tuple<int, int> recoverWindowSize() = 0;
};

#endif /* !IDISPLAY_HPP_ */
