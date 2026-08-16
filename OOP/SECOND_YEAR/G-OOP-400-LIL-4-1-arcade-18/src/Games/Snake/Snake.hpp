/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

#include "IGame.hpp"
#include <deque>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <vector>

enum TileType {
    EMPTY,
    WALL,
    SNAKE_HEAD,
    SNAKE_BODY,
    FOOD,
    GOLDEN_FOOD
};

enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

struct Tile {
    TileType type;
};

struct Position {
    int x, y;
};

class Snake : public IGame
{
    private:
        std::deque<Position> body;
        Direction dir = Direction::RIGHT;
        Direction nextDir = Direction::RIGHT;
        bool dead = false;
        int width = 26;
        int height = 20;
        std::vector<std::vector<Tile>> grid;
        std::tuple<int, int> coord_golden;
        std::size_t tick = {0};

        void initializeGrid();
        void spawnFood(TileType Typefood);
        void updateSnake();
        int getDirX(Direction d);
        int getDirY(Direction d);
        void check_angle(int y, int x);

    public:
        Snake();
        ~Snake();
        void update(InputEvent key) override;
        bool isOver() override;
        std::vector<Sprite> getSprites() override;
        std::vector<Texte> getTextes() override;
        std::vector<std::string> getSounds() override;
        std::size_t getScore() override;
};

#endif /* !SNAKE_HPP_ */
