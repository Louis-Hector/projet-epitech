/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Snake
*/

#include "Snake.hpp"

Snake::Snake()
{
    _name = "snake";
    _type = LibType::GAME;
    srand(time(nullptr));
    initializeGrid();
}

Snake::~Snake() {}

int Snake::getDirX(Direction direction) {
    switch (direction) {
        case Direction::LEFT:
            return -1;
        case Direction::RIGHT:
            return 1;
        default:
            return 0;
    }
}

int Snake::getDirY(Direction direction)
{
    switch (direction) {
        case Direction::UP:
            return -1;
        case Direction::DOWN:
            return 1;
        default:
            return 0;
    }
}

void Snake::initializeGrid()
{
    grid = std::vector<std::vector<Tile>>(height, std::vector<Tile>(width));
    
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            grid[y][x].type = TileType::EMPTY;
    for (int x = 0; x < width; x++) {
        grid[0][x].type = TileType::WALL;
        grid[height - 1][x].type = TileType::WALL;
    }
    for (int y = 0; y < height; y++) {
        grid[y][0].type = TileType::WALL;
        grid[y][width - 1].type = TileType::WALL;
    }
    body.clear();
    body.push_back({width / 2, height / 2});
    body.push_back({width / 2 - 1, height / 2});
    body.push_back({width / 2 - 2, height / 2});
    body.push_back({width / 2 - 3, height / 2});
    grid[body[0].y][body[0].x].type = TileType::SNAKE_HEAD;
    for (size_t i = 1; i < body.size(); ++i)
        grid[body[i].y][body[i].x].type = TileType::SNAKE_BODY;
    spawnFood(TileType::FOOD);
}

void Snake::spawnFood(TileType Typefood)
{
    int x = 0;
    int y = 0;
    int attempts = width * height;

    while (attempts > 0 && grid[y][x].type != TileType::EMPTY) {
        x = 1 + rand() % (width - 2);
        y = 1 + rand() % (height - 2);
        attempts--;
    }
    if (grid[y][x].type != TileType::EMPTY)
        return;
    if (Typefood == TileType::FOOD)
        grid[y][x].type = TileType::FOOD;
    else {
        grid[y][x].type = TileType::GOLDEN_FOOD;
        coord_golden = std::make_tuple(y, x);
    }
}

void Snake::updateSnake()
{
    dir = nextDir;
    Position newHead = {
        body.front().x + getDirX(dir),
        body.front().y + getDirY(dir)
    };
    bool out_of_bounds = newHead.x < 0 || newHead.x >= width || newHead.y < 0 || newHead.y >= height;

    if (out_of_bounds) {
        dead = true;
        _sounds.push_back("game_over");
        return;
    }
    TileType next_tile = grid[newHead.y][newHead.x].type;
    bool ateFood = (next_tile == TileType::FOOD);
    bool ategoldenApple = (next_tile == TileType::GOLDEN_FOOD);

    if (next_tile == TileType::WALL || next_tile == TileType::SNAKE_BODY) {
        dead = true;
        _sounds.push_back("game_over");
        return;
    }
    body.push_front(newHead);
    grid[newHead.y][newHead.x].type = TileType::SNAKE_HEAD;
    if ((1 + rand() % 100) % 100 == 0 && std::get<0>(coord_golden) == 0)
        spawnFood(TileType::GOLDEN_FOOD);
    else if (std::get<0>(coord_golden) != 0 && tick % 25 == 0) {
        grid[std::get<0>(coord_golden)][std::get<1>(coord_golden)].type = TileType::EMPTY;
        coord_golden = std::make_tuple(0, 0);
        tick = 0;
    }
    if (ateFood) {
        spawnFood(TileType::FOOD);
        _sounds.push_back("eat");
        _score += 1;
    } else if (ategoldenApple) {
        _sounds.push_back("eat");
        auto last = body.back();
        for (std::size_t i = 0; i < 3; i++)
            body.push_back(last);
        _score += 3;
    } else {
        Position tail = body.back();
        body.pop_back();
        grid[tail.y][tail.x].type = TileType::EMPTY;
    }
    if (body.size() > 1)
        grid[body[1].y][body[1].x].type = TileType::SNAKE_BODY;
}

void Snake::update(InputEvent key)
{
    if (key.event == UP_ARROW && dir != Direction::DOWN)
        nextDir = Direction::UP;
    if (key.event == DOWN_ARROW && dir != Direction::UP)
        nextDir = Direction::DOWN;
    if (key.event == LEFT_ARROW && dir != Direction::RIGHT)
        nextDir = Direction::LEFT;
    if (key.event == RIGHT_ARROW && dir != Direction::LEFT) 
        nextDir = Direction::RIGHT;
    if (std::get<0>(coord_golden) != 0)
        tick += 1;
    _sounds.clear();
    updateSnake();
}

bool Snake::isOver()
{
    return dead;
}

void Snake::check_angle(int y, int x)
{
    if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1)
        return;
    TileType body = TileType::SNAKE_BODY;
    TileType head = TileType::SNAKE_HEAD;
    TileType griddown = grid[y - 1][x].type;
    TileType gridup = grid[y + 1][x].type;
    TileType gridright = grid[y][x + 1].type;
    TileType gridleft = grid[y][x - 1].type;

    if ((gridright == body || gridright == head) && (gridleft == body || gridleft == head))
        _sprites.push_back({x, y, 0, 1.0f, "body_horizontal"});
    else if ((gridup == body || gridup == head) && (griddown == body || griddown == head))
        _sprites.push_back({x, y, 0, 1.0f, "body_vertical"});
    else if ((gridup == body || gridup == head) && (gridleft == body || gridleft == head))
        _sprites.push_back({x, y, 0, 1.0f, "body_up_left"});
    else if ((gridup == body || gridup == head) && (gridright == body || gridright == head))
        _sprites.push_back({x, y, 0, 1.0f, "body_up_right"});
    else if ((griddown == body || griddown == head) && (gridright == body || gridright == head))
        _sprites.push_back({x, y, 0, 1.0f, "body_down_right"});
    else if ((griddown == body || griddown == head) && (gridleft == body || gridleft == head))
        _sprites.push_back({x, y, 0, 1.0f, "body_down_left"});
}

std::vector<Sprite> Snake::getSprites()
{
    _sprites.clear();

    _sprites.push_back({0, 0, 0, 1.0f, "background"});
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x].type == TileType::SNAKE_HEAD) {
                switch (dir) {
                case Direction::RIGHT:
                    _sprites.push_back({x, y, 0, 1.0f, "snake_right"});
                    break;
                case Direction::LEFT:
                    _sprites.push_back({x, y, 0, 1.0f, "snake_left"});
                    break;
                case Direction::UP:
                    _sprites.push_back({x, y, 0, 1.0f, "snake_up"});
                    break;
                case Direction::DOWN:
                    _sprites.push_back({x, y, 0, 1.0f, "snake_down"});
                    break;
                default:
                    break;
                }
            }
            if (grid[y][x].type == TileType::SNAKE_BODY)
                check_angle(y, x);
            if (grid[y][x].type == TileType::FOOD)
                _sprites.push_back({x, y, 0, 1.1f, "apple"});
            if (grid[y][x].type == TileType::GOLDEN_FOOD)
                _sprites.push_back({x, y, 0, 1.1f, "golden_apple"});
        }
    }
    return _sprites;
}

std::vector<std::string> Snake::getSounds()
{
    return _sounds;
}

std::vector<Texte> Snake::getTextes()
{
    _texts.clear();
    _texts.push_back({27, 4, 1.0, "Score :", RED});
    _texts.push_back({28, 5, 1.0, std::to_string(_score), RED});
    return _texts;
}

std::size_t Snake::getScore()
{
    return _score;
}

extern "C" IGame *entryPoint()
{
    return new Snake();
}
