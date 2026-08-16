/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Tetris
*/
#ifndef TETRIS_HPP_
#define TETRIS_HPP_

#include "IGame.hpp"
#include <random>
#include <vector>
#include <array>
#include <algorithm>

struct Piece {
    int type;
    int rotation;
    int x;
    int y;
};

class Tetris : public IGame
{
    private:
        struct Cell {
            int x;
            int y;
        };
        static const int BOARD_WIDTH = 10;
        static const int BOARD_HEIGHT = 20;
        static const int BOARD_OFFSET_X = 8;
        static const int PIECE_COUNT = 7;
        static const int ROTATION_COUNT  = 4;
        static const int CELLS_PER_PIECE = 4; 
        bool _dead  = false;
        int _tick  = 0;
        std::size_t _lines = 0;
        std::vector<std::vector<int>> _board;
        Piece _current = {0, 0, 0, 0};
        Piece _next = {0, 0, 0, 0};
        std::mt19937 _rng;
        static const std::array<std::array<Cell, CELLS_PER_PIECE>, PIECE_COUNT> BASE_SHAPES;

        static std::array<Cell, CELLS_PER_PIECE> rotate(const std::array<Cell, CELLS_PER_PIECE> &cells);
        static std::array<std::array<Cell, CELLS_PER_PIECE>, ROTATION_COUNT> buildRotations(const std::array<Cell, CELLS_PER_PIECE> &base);
        static std::array<std::array<std::array<Cell, CELLS_PER_PIECE>, ROTATION_COUNT>, PIECE_COUNT> buildAllShapes();
        static const std::array<Cell, CELLS_PER_PIECE> &getCells(const Piece &p);
        Piece randomPiece();
        void spawnNewPiece();
        bool canPlace(const Piece &piece, int dx, int dy, int newRotation) const;
        bool tryMove(int dx, int dy);
        bool tryRotate();
        void lockCurrentPiece();
        int clearLines();
        int gravitySpeed() const;
        std::string spriteNameFromType(int type) const;

    public:
        Tetris();
        ~Tetris();

        void update(InputEvent key) override;
        bool isOver() override;
        std::size_t getScore() override;
        std::vector<Sprite> getSprites() override;
        std::vector<Texte> getTextes() override;
        std::vector<std::string> getSounds() override;
};

#endif /* !TETRIS_HPP_ */