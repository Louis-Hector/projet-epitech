/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Ncurses::Ncurses(/* args */)
{
    _name = "Ncurses";
    _type = LibType::DISPLAY;
    window_menu = nullptr;
    window_game = nullptr;
}

int Ncurses::createWindow()
{
    if (initscr() == NULL)
        return -1;
    clear();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    use_default_colors();
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    int xMax = 0;
    int yMax = 0;
    getmaxyx(stdscr, yMax, xMax);
    if (xMax < 120 || yMax < 25 || (xMax / 2) - 15 - 50 < 0
        || (yMax / 2) - 10 < 0 || (xMax / 2) - 13 < 0 || (yMax / 2) - 10 < 0) {
        endwin();
        std::cout << "The size of the window is not enough" << std::endl;
        return -1;
    }
    window_menu = newwin(20, 50, (yMax / 2) - 10, (xMax / 2) - 15 - 50);
    window_game = newwin(20, 26, (yMax / 2) - 10, (xMax / 2) - 13);
    if (!window_game || !window_menu) {
        endwin();
        return -1;
    }
    widthWindow = 50;
    heightWindow = 20;
    wborder(window_menu, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(window_game, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(window_menu);
    wrefresh(window_game);
    _colors = {{WHITE, 1}, {BLUE, 2}, {YELLOW, 3}, {RED, 4}, {MAGENTA, 5}, {CYAN, 6}};
    init_pair(1, COLOR_WHITE, -1);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_RED, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(6, COLOR_CYAN, -1);
    timeout(50);
    return 0;
}


std::tuple<int, int> Ncurses::recoverWindowSize()
{ 
    return std::make_tuple<int, int>(widthWindow, heightWindow);
}


void Ncurses::closeWindow()
{
    if (window_menu) {
        delwin(window_menu);
        window_menu = nullptr;
    }
    if (window_game) {
        delwin(window_game);
        window_game = nullptr;
    }
    endwin();
}

void Ncurses::clear()
{
    if (window_menu) {
        werase(window_menu);
        wborder(window_menu, '|', '|', '-', '-', '+', '+', '+', '+');
    }
    if (window_game) {
        werase(window_game);
        wborder(window_game, '|', '|', '-', '-', '+', '+', '+', '+');
    }
}

void Ncurses::display()
{
    if (window_menu)
        wrefresh(window_menu);
    if (window_game)
        wrefresh(window_game);
    return;
}

InputEvent Ncurses::getInput()
{
    InputEvent action = {};
    int input = getch();
    const std::map<int, EventType> list_key_event = {{'g', EventType::SWITCH_GAME}, {'l', EventType::SWITCH_DISPLAY}, {'m', EventType::CALL_MENU}, {' ', EventType::SPACE},
        {'\n', EventType::ENTER}, {KEY_ENTER, EventType::ENTER}, {'q', EventType::QUIT}, {27, EventType::QUIT}, {'r', EventType::RESTART_GAME},
        {KEY_UP, EventType::UP_ARROW}, {KEY_DOWN, EventType::DOWN_ARROW}, {KEY_RIGHT, EventType::RIGHT_ARROW}, {KEY_LEFT, EventType::LEFT_ARROW}};

    if (input == KEY_MOUSE) {
        MEVENT mouse;
        if (!window_game)
            return action;
        if (getmouse(&mouse) == OK) {
            int x = {};
            int y = {};
            getbegyx(window_game, y, x);
            if (mouse.y >= y && mouse.y < y + 20 && mouse.x >= x && mouse.x < x + 30) {
                action.mouse = {mouse.x - x, mouse.y - y};
                if (mouse.bstate & BUTTON1_CLICKED)
                    action.event = EventType::LEFT_CLICK;
                if (mouse.bstate & BUTTON3_CLICKED)
                    action.event = EventType::RIGHT_CLICK;
            }
        }
        return action;
    }
    auto elem = list_key_event.find(input);
    if (elem == list_key_event.end())
        return action;
    action.event = elem->second;
    return action;
}

void Ncurses::drawBackground(std::string background_name)
{
    (void)background_name;
    return;
}

void Ncurses::drawText(pos position, float size, std::string text, Color color)
{
    (void)size;
    short drawcolor = COLOR_PAIR(0);

    auto elem = _colors.find(color);
    if (elem == _colors.end())
        return;
    drawcolor = elem->second;
    int x_d = {position.x};
    if (position.x == -1)
        x_d = ((widthWindow - text.size()) / 2);
    wattron(window_menu, COLOR_PAIR(drawcolor));
    mvwprintw(window_menu, position.y, x_d, "%s", text.c_str());
    wattroff(window_menu, COLOR_PAIR(drawcolor));
    return;
}
 
void Ncurses::drawSprite(pos position, int rotation, float size, std::string name)
{
    (void)rotation;
    (void)size;
    auto elem = _textures.find(name);
    if (elem == _textures.end())
        return;
    mvwprintw(window_game, position.y , position.x , "%c", elem->second);
    return;
}

int Ncurses::loadTexture(std::string game)
{
    _textures.clear();
    std::string directory_name = "assets/" + game + "/ascii";
    try {
        for (const auto &Entry : std::filesystem::directory_iterator(directory_name)) {
            if (Entry.is_directory())
                continue;
            auto file = Entry.path().string();
            auto pos_exten = file.find_last_of('.');
            if (pos_exten == std::string::npos || file.substr(pos_exten + 1) != "txt")
                continue;
            auto name = Entry.path().stem().string();
            std::ifstream file_content = std::ifstream(file);
            std::string line;
            std::getline(file_content, line);
            if (line.size() == 1)
                _textures[name] = line[0];
        }
    } catch (const std::exception &) {
        return -1;
    }
    return 0;
}

int Ncurses::loadSound(std::string game)
{
    (void)game;
    return 0;
}

std::string Ncurses::loadName()
{
    std::string name = "";
    int ch = {};
    int pos = 20;

    wrefresh(window_menu);
    wmove(window_menu, 10, pos);
    wrefresh(window_menu);
    curs_set(1);
    while (1)
    {
        ch = getch();
        if (ch == '\n' || name.size() > 15)
            break;
        if (isprint(ch) && ch != ' ') {
            name += ch;
            waddch(window_menu, ch);
            pos += 1;
        }
        wrefresh(window_menu);
        wmove(window_menu, 10, pos);
        wrefresh(window_menu);
    }
    curs_set(0);
    if (name.size() == 0)
        name = "Guest";
    return name;
}

int Ncurses::playSound(std::string sound_name_in_map)
{
    (void)sound_name_in_map;
    return 0;
}

extern "C" IDisplay *entryPoint()
{
    return new Ncurses();
}
