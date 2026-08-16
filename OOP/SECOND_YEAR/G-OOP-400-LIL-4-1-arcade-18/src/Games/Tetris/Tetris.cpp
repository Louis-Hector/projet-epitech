/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Tetris
*/

#include "Tetris.hpp"

const std::array<std::array<Tetris::Cell, Tetris::CELLS_PER_PIECE>,
Tetris::PIECE_COUNT> Tetris::BASE_SHAPES = {{
    {{{0,1},{1,1},{2,1},{3,1}}}, // I
    {{{1,0},{2,0},{1,1},{2,1}}}, // O
    {{{1,0},{0,1},{1,1},{2,1}}}, // T
    {{{1,0},{2,0},{0,1},{1,1}}}, // S
    {{{0,0},{1,0},{1,1},{2,1}}}, // Z
    {{{0,0},{0,1},{1,1},{2,1}}}, // J
    {{{2,0},{0,1},{1,1},{2,1}}}, // L
}};

std::array<Tetris::Cell, Tetris::CELLS_PER_PIECE>
Tetris::rotate(const std::array<Cell, CELLS_PER_PIECE> &cells)
{
    std::array<Cell, CELLS_PER_PIECE> result;

    for (int i = 0; i < CELLS_PER_PIECE; ++i)
        result[i] = {3 - cells[i].y, cells[i].x};
    return result;
}

std::array<std::array<Tetris::Cell, Tetris::CELLS_PER_PIECE>, Tetris::ROTATION_COUNT>
Tetris::buildRotations(const std::array<Cell, CELLS_PER_PIECE> &base)
{
    std::array<std::array<Cell, CELLS_PER_PIECE>, ROTATION_COUNT> rotations;

    rotations[0] = base;
    for (int i = 1; i < ROTATION_COUNT; ++i)
        rotations[i] = rotate(rotations[i - 1]);
    return rotations;
}

std::array<std::array<std::array<Tetris::Cell, Tetris::CELLS_PER_PIECE>,
Tetris::ROTATION_COUNT>, Tetris::PIECE_COUNT> Tetris::buildAllShapes()
{
    std::array<std::array<std::array<Cell, CELLS_PER_PIECE>, ROTATION_COUNT>, PIECE_COUNT> shapes;

    for (int i = 0; i < PIECE_COUNT; ++i)
        shapes[i] = buildRotations(BASE_SHAPES[i]);
    return shapes;
}

const std::array<Tetris::Cell, Tetris::CELLS_PER_PIECE> &Tetris::getCells(const Piece &p)
{
    static const auto SHAPES = buildAllShapes();

    return SHAPES[p.type][((p.rotation % ROTATION_COUNT) + ROTATION_COUNT) % ROTATION_COUNT];
}

Tetris::Tetris() : _rng(std::random_device{}())
{
    _name = "tetris";
    _type = LibType::GAME;
    _board.assign(BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 0));
    _current = randomPiece();
    _next = randomPiece();

    if (!canPlace(_current, 0, 0, _current.rotation)) {
        _dead = true;
        _sounds.push_back("game_over");
    }
}

Tetris::~Tetris() {}

Piece Tetris::randomPiece()
{
    std::uniform_int_distribution<int> dist(0, PIECE_COUNT - 1);

    return {dist(_rng), 0, (BOARD_WIDTH / 2) - 2, 0};
}

void Tetris::spawnNewPiece()
{
    _current = _next;
    _next = randomPiece();

    if (!canPlace(_current, 0, 0, _current.rotation)) {
        _dead = true;
        _sounds.push_back("game_over");
    }
}

bool Tetris::canPlace(const Piece &piece, int dx, int dy, int newRotation) const
{
    for (const auto &cell : getCells({piece.type, newRotation, 0, 0})) {
        int x = piece.x + dx + cell.x;
        int y = piece.y + dy + cell.y;
        bool outOfBounds = x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT;

        if (outOfBounds || _board[y][x] != 0)
            return false;
    }
    return true;
}

bool Tetris::tryMove(int dx, int dy)
{
    if (!canPlace(_current, dx, dy, _current.rotation))
        return false;
    _current.x += dx;
    _current.y += dy;
    return true;
}

bool Tetris::tryRotate()
{
    int nextRotation = (_current.rotation + 1) % ROTATION_COUNT;
    static const std::array<int, 5> kicks = {0, -1, 1, -2, 2};

    for (int kick : kicks) {
        if (!canPlace(_current, kick, 0, nextRotation))
            continue;
        _current.rotation = nextRotation;
        _current.x += kick;
        return true;
    }
    return false;
}

void Tetris::lockCurrentPiece()
{
    for (const auto &cell : getCells(_current)) {
        int x = _current.x + cell.x;
        int y = _current.y + cell.y;

        if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
            _board[y][x] = _current.type + 1;
    }

    int cleared = clearLines();
    if (cleared > 0) {
        _lines += cleared;
        _score += static_cast<std::size_t>(100 * cleared * cleared);
        _sounds.push_back("win");
    }
    spawnNewPiece();
}

int Tetris::clearLines()
{
    int cleared = 0;

    for (int y = BOARD_HEIGHT - 1; y >= 0; --y) {
        bool full = std::all_of(_board[y].begin(), _board[y].end(),
            [](int cell) { return cell != 0; });

        if (!full)
            continue;
        _board.erase(_board.begin() + y);
        _board.insert(_board.begin(), std::vector<int>(BOARD_WIDTH, 0));
        ++cleared;
        ++y;
    }
    return cleared;
}

int Tetris::gravitySpeed() const
{
    int level = 1 + static_cast<int>(_lines / 10);

    return std::max(1, 8 - level);
}

void Tetris::update(InputEvent key)
{
    if (_dead)
        return;
    switch (key.event) {
        case EventType::LEFT_ARROW:
            tryMove(-1, 0);
            break;
        case EventType::RIGHT_ARROW:
            tryMove( 1, 0);
            break;
        case EventType::UP_ARROW:
            tryRotate();
            break;
        case EventType::DOWN_ARROW:
            if (tryMove(0, 1))
                _score += 1;
            else
                lockCurrentPiece();
            _tick = 0;
            break;
        default:
            break;
    }
    if (_dead)
        return;
    if (++_tick >= gravitySpeed()) {
        if (!tryMove(0, 1))
            lockCurrentPiece();
        _tick = 0;
    }
}

bool Tetris::isOver()
{
    return _dead;
}

std::size_t Tetris::getScore()
{
    return _score;
}

std::string Tetris::spriteNameFromType(int type) const
{
    if (type >= 1 && type <= PIECE_COUNT)
        return "Tile" + std::to_string(type);
    return "TileUnknown";
}

std::vector<Sprite> Tetris::getSprites()
{
    _sprites.clear();
    _sprites.push_back({0, 0, 0, 1.0f, "background"});

    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            _sprites.push_back({BOARD_OFFSET_X + x, y, 0, 1.0f, "TileEmpty"});
            if (_board[y][x] != 0)
                _sprites.push_back({BOARD_OFFSET_X + x, y, 0, 1.0f,
                    spriteNameFromType(_board[y][x])});
        }
    }
    for (const auto &cell : getCells(_current)) {
        int x = _current.x + cell.x;
        int y = _current.y + cell.y;

        if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
            _sprites.push_back({BOARD_OFFSET_X + x, y, 0, 1.0f,
                spriteNameFromType(_current.type + 1)});
    }
    for (const auto &cell : getCells({_next.type, 0, 0, 0}))
        _sprites.push_back({21 + cell.x, 4 + cell.y, 0, 1.0f,
            spriteNameFromType(_next.type + 1)});
    return _sprites;
}

std::vector<Texte> Tetris::getTextes()
{
    int row = 4;
    const std::pair<std::string, std::string> entries[] = {
        {"Score: ", std::to_string(_score)},
        {"Lines: ", std::to_string(_lines)},
    };

    _texts.clear();
    for (const auto &[label, value] : entries) {
        _texts.push_back({27, row, 1.0f, label, RED});
        _texts.push_back({28, row + 1, 1.0f, value, RED});
        row += 3;
    }
    return _texts;
}

std::vector<std::string> Tetris::getSounds()
{
    std::vector<std::string> sounds = _sounds;

    _sounds.clear();
    return sounds;
}

extern "C" IGame *entryPoint()
{
    return new Tetris();
}