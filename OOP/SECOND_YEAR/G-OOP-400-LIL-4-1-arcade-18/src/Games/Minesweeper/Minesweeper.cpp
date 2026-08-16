/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Minesweeper
*/

#include "Minesweeper.hpp"

Minesweeper::Minesweeper(/* args */)
{
    _name = "minesweeper";
    _type = LibType::GAME;
    initializeGrid();
}

Minesweeper::~Minesweeper()
{
}

bool Minesweeper::is_inside_board(int x, int y) const
{
    return x >= 0 && y >= 0 && x < height && y < width;
}

int Minesweeper::count_adja_bombs(int x, int y)
{
    int count = 0;

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y)
                continue;
            if (i < 0 || i >= height || j < 0 || j >= width)
                continue;
            if (_grid[i][j] == '*')
                count++;
        }
    }
    return count;
}

void Minesweeper::initializeGrid()
{
    _grid = std::vector<std::vector<char>>(height, std::vector<char>(width));
    _reveal = std::vector<std::vector<bool>>(height, std::vector<bool>(width));
    _flags = std::vector<std::vector<bool>>(height, std::vector<bool>(width));
    _imark = std::vector<std::vector<bool>>(height, std::vector<bool>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            _grid[i][j] = ' ';
            _reveal[i][j] = false;
            _flags[i][j] = false;
            _imark[i][j] = false;
        }
    }
}

void Minesweeper::set_mines_and_values(int start_player_x, int start_player_y)
{
    for (int i = start_player_x - 1; i <= start_player_x + 1; i++) {
        for (int j = start_player_y - 1; j <= start_player_y + 1; j++) {
            if (i < 0 || j < 0 || i >= height || j >= width)
                continue;
            _grid[i][j] = '0';
        }
    }
    int i = {0};
    while (i < nb_bombs) {
        int x = rand() % height;
        int y = rand() % width;
        if (_grid[x][y] != ' ')
           continue;
        _grid[x][y] = '*';
        i++;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (_grid[i][j] == '*')
                continue;
            _grid[i][j] = '0' + count_adja_bombs(i, j);
        }
    }
}

void Minesweeper::reveal_map(int x, int y)
{
    if (x < 0 || y < 0 || x >= height || y >= width || _reveal[x][y] == true)
        return;
    if (_flags[x][y] == true)
        return;
    if (_grid[x][y] == '*') {
        last_coord = std::make_tuple(x, y);
        _sounds.push_back("game_over");
        dead = true;
        return;
    }
    _score += 1;
    _reveal[x][y] = true;
    if (_grid[x][y] != '0')
        return;
    for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
            reveal_map(i, j);
    return;
}

void Minesweeper::update(InputEvent key)
{
    _sounds.clear();
    if (start_game == false) {
        if (key.event == EventType::LEFT_CLICK || key.event == EventType::RIGHT_CLICK) {
            if (!is_inside_board(key.mouse.y, key.mouse.x))
                return;
            set_mines_and_values(key.mouse.y, key.mouse.x);
            reveal_map(key.mouse.y, key.mouse.x);
            start_game = true;
        }
        return;
    }
    time -= 1;
    if (time == 0) {
        _sounds.push_back("game_over");
        dead = true;
        return;
    }
    if (key.event == EventType::LEFT_CLICK && is_inside_board(key.mouse.y, key.mouse.x))
        reveal_map(key.mouse.y, key.mouse.x);
    if (key.event == EventType::RIGHT_CLICK) {
        auto x = key.mouse.y;
        auto y = key.mouse.x;
        if (!is_inside_board(x, y))
            return;
        if (_flags[x][y] == false && _reveal[x][y] == false && _imark[x][y] == false) {
            _flags[x][y] = true;
            nb_flags += 1;
        } else if (_flags[x][y] == true && _imark[x][y] == false) { 
            _flags[x][y] = false;
            nb_flags -= 1;
            _imark[x][y] = true;
        } else if (_imark[x][y] == true)
            _imark[x][y] = false;
    }   
    return;
}

bool Minesweeper::isOver()
{
    int nb_good_flags = {};
    int nb_tile_reveal = {};

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (_grid[x][y] == '*' && _flags[x][y] == true)
                nb_good_flags += 1;
            else if (_grid[x][y] != '*' && _flags[x][y] == true)
                nb_good_flags -= 1;
            if (_reveal[x][y] == true)
                nb_tile_reveal += 1;
        }
    }
    if (nb_good_flags == nb_bombs && nb_tile_reveal == width * height - nb_bombs) {
        _sounds.push_back("win");
        _score += time / 10;
        dead = true;
    }
    return dead;
}

std::vector<Sprite> Minesweeper::getSprites() 
{
    _sprites.clear();

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (dead == true && _grid[x][y] == '*' && x != std::get<0>(last_coord))
                _sprites.push_back({y, x, 0, 1.0f, "TileMine"});
            else if (dead == true && x == std::get<0>(last_coord) && y == std::get<1>(last_coord))
                _sprites.push_back({y, x, 0, 1.0f, "TileExploded"});
            else if (_flags[x][y] == true && _reveal[x][y] == false)
                _sprites.push_back({y, x, 0, 1.0f, "TileFlag"});
            else if (_grid[x][y] == '0' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "TileEmpty"});
            else if (_imark[x][y] == true && _reveal[x][y] == false)
                _sprites.push_back({y, x, 0, 1.0f, "interrogation"});
            else if (_grid[x][y] == '1' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "Tile1"});
            else if (_grid[x][y] == '2' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "Tile2"});
            else if (_grid[x][y] == '3' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "Tile3"});
            else if (_grid[x][y] == '4' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "Tile4"});
            else if (_grid[x][y] == '5' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "Tile5"});
            else if (_grid[x][y] == '6' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "Tile6"});
            else if (_grid[x][y] == '7' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "Tile7"});
            else if (_grid[x][y] == '8' && _reveal[x][y] == true)
                _sprites.push_back({y, x, 0, 1.0f, "Tile8"});
            else
                _sprites.push_back({y, x, 0, 1.0f, "TileUnknown"});
        }
    }
    return _sprites;
}

std::vector<Texte> Minesweeper::getTextes() 
{
    _texts.clear();
    _texts.push_back({27, 4, 1.0, "Score :", RED});
    _texts.push_back({28, 5, 1.0, std::to_string(_score), RED});
    _texts.push_back({27, 7, 1, "Time :", RED});
    _texts.push_back({27, 8, 1, std::to_string(time), RED});
    _texts.push_back({27, 10, 1, "Flags : ", RED});
    _texts.push_back({27, 11, 1, std::to_string(nb_bombs - nb_flags), RED});
    return _texts;
}

std::vector<std::string> Minesweeper::getSounds() 
{
    return _sounds;
}

std::size_t Minesweeper::getScore()
{
    return _score;
}

extern "C" IGame *entryPoint()
{
    return new Minesweeper();
}
