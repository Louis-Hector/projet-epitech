/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Minesweeper
*/

#ifndef MINESWEEPER_HPP_
#define MINESWEEPER_HPP_

#include "IGame.hpp"

class Minesweeper : public IGame
{
private:
    int height = {20};
    int width = {26};
    int nb_bombs = {100};
    int nb_flags = {0};
    int time = {10000};
    std::tuple<int, int> last_coord;
    bool dead = false;
    bool start_game = false;
    std::vector<std::vector<char>> _grid;
    std::vector<std::vector<bool>> _reveal;
    std::vector<std::vector<bool>> _flags;
    std::vector<std::vector<bool>> _imark;

    void initializeGrid();
    void set_mines_and_values(int start_player_x, int start_player_y);
    int count_adja_bombs(int x, int y);
    void reveal_map(int x, int y);
    bool is_inside_board(int x, int y) const;
public:
    Minesweeper(/* args */);
    ~Minesweeper();
    void update(InputEvent key) override;
    bool isOver() override;
    std::vector<Sprite> getSprites() override;
    std::vector<Texte> getTextes() override;
    std::vector<std::string> getSounds() override;
    std::size_t getScore() override;
};

#endif /* !MINESWEEPER_HPP_ */
