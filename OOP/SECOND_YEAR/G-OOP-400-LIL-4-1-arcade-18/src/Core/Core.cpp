/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Core
*/

#include "Core.hpp"
#include <unistd.h>
#include <csignal>

volatile std::sig_atomic_t Core::sigint_received = 0;

void Core::handle_sigint(int)
{
    sigint_received = 1;
}

Core::Core(std::vector<std::string> &_parse_libs, std::vector<std::string> &_parse_games) : 
    _list_graph(_parse_libs), _list_games(_parse_games)
{
}

Core::~Core()
{
    if (graph) {
        graph->closeWindow();
        graph.reset();
    }
    game.reset();
    _dl_game.close_lib();
    _dl_graph.close_lib();
}

Core::CoreError::CoreError(std::string error) : _msg(error)
{
}

const char * Core::CoreError::what() const noexcept
{
    return _msg.c_str();
}

template <typename T>
std::unique_ptr<T> Core::recover_lib(const char *path_lib, Libdl &_dl)
{
    const std::string lib_path = path_lib ? std::string(path_lib) : "unknown library path";

    if (_dl.open_lib(path_lib) == false)
        throw CoreError("Error during open the lib : " + lib_path);
    auto module = (T * (*)(void))_dl.search_elem("entryPoint");
    if (module == NULL)
        throw CoreError("Invalid functions in : " + lib_path);
    auto instance = module();
    if (!instance)
        throw CoreError("entryPoint returned null in : " + lib_path);
    return std::unique_ptr<T>(instance);
}

void Core::reloads_libs(bool is_graphical, bool is_game)
{
    if (is_graphical == true) {
        graph->closeWindow();
        graph.reset();
        _dl_graph.close_lib();
        graph = recover_lib<IDisplay>(_list_graph[_index_graph].c_str(), _dl_graph);
        if (graph->createWindow() == -1)
            throw CoreError("Impossible to init the lib : " + graph->get_name());
    }
    if (is_game == true) {
        game.reset();
        _dl_game.close_lib();
        game = recover_lib<IGame>(_list_games[_index_game].c_str(), _dl_game);
    }
    if (game && (graph->loadTexture(game->get_name()) == -1 || graph->loadSound(game->get_name()) == -1))
        throw CoreError("Error during load for assets");
}

void Core::show_available_list(std::unique_ptr<IDisplay> &graph)
{
    int pos = 4;

    graph->drawText({-1, 1}, 1.0f, "The graphics libraries and the games libraries :", WHITE);
    graph->drawText({-1, 3}, 1.0f, "List of available librarys (Switch with L)", YELLOW);
    std::string _lib = _list_graph[_index_graph];
    graph->drawText({-1, pos}, 1.0f, "> " + _lib, WHITE);
    pos += 1;
    graph->drawText({-1, pos + 1}, 1.0f, "List of available games (Switch with G)", YELLOW);
    pos += 2;
    std::string _game = _list_games.empty() ? "No game loaded" : _list_games[_index_game];
    graph->drawText({-1, pos}, 1.0f, "> " + _game, WHITE);
    pos += 2;
    graph->drawText({-1, pos}, 1.0f, "Please enter your username :", YELLOW);
    if (!_name.empty())
        graph->drawText({-1, pos + 1}, 1.0f, "Your name : " + _name, BLUE);
    pos += 3;
    graph->drawText({-1, pos}, 1.0, "Leaderboard for the actual game", YELLOW);
    pos += 1;
    int i = {1};
    for (auto &score : _scoreboard) {
        graph->drawText({-1, pos}, 1.0f, std::to_string(i) + ". " + score.first + " " + std::to_string(score.second), RED);
        i++;
        pos += 1;
    }
}

int Core::handle_input_menu(InputEvent input, bool &is_menu, std::unique_ptr<IDisplay> &lib_menu)
{
    if (input.event == EventType::SWITCH_DISPLAY && !_list_graph.empty())
        _index_graph = (_index_graph + 1) % _list_graph.size();
    if (input.event == EventType::SWITCH_GAME && !_list_games.empty())
        _index_game = (_index_game + 1) % _list_games.size();
    if (input.event == EventType::ENTER) {
        is_menu = false;
    }
    if (input.event == EventType::QUIT) {
        is_menu = false;
        lib_menu->closeWindow();
        lib_menu.reset();
        game.reset();
        _dl_game.close_lib();
        _dl_graph.close_lib();
        return 1;
    }
    return 0;
}

std::string Core::get_scoreboard_file()
{
    std::string scoreboard_filename;
    std::string path_lib = _list_games[_index_game];
    size_t index_slash = path_lib.find_last_of("/");
    size_t index_dot;

    if (index_slash == std::string::npos)
        scoreboard_filename = path_lib.substr(0);
    else
        scoreboard_filename = path_lib.substr(index_slash + 1);
    index_dot = scoreboard_filename.find_last_of('.');
    if (index_dot != std::string::npos)
        scoreboard_filename = scoreboard_filename.substr(0, index_dot);
    return "scores/" + scoreboard_filename + "_score.txt";
}

void Core::parse_scoreboard()
{
    std::ifstream file(get_scoreboard_file());
    std::vector<std::pair<std::string, int>> scoreboard;
    std::string name;
    int value;

    _scoreboard.clear();
    if (!file)
        return;
    while (file >> name >> value)
        scoreboard.push_back({name, value});
    file.close();
    std::sort(scoreboard.begin(), scoreboard.end(),
        [](auto& first_pair, auto& second_pair) {
            return first_pair.second > second_pair.second;
        });
    _scoreboard = scoreboard;
}

void Core::store_scoreboard(std::string name_player, int score)
{
    std::ofstream file(get_scoreboard_file(), std::ios::out | std::ios::trunc);

    if (!file)
        return;
    if (_scoreboard.size() < 3)
        _scoreboard.push_back({name_player, score});
    else
        if (_scoreboard.back().second < score)
            _scoreboard.back() = {name_player, score};
    std::sort(_scoreboard.begin(), _scoreboard.end(),
        [](auto& first_pair, auto& second_pair) {
            return first_pair.second > second_pair.second;
        });
    if (!file)
        return;
    for (const auto &player : _scoreboard)
        file << player.first << " " << player.second << std::endl;
}

int Core::launch_menu()
{
    graph = recover_lib<IDisplay>((_list_graph[_index_graph]).c_str(), _dl_graph);
    bool is_menu = true;

    if (graph->createWindow() == -1)
        throw CoreError("Impossible to init the lib : " + graph->get_name());
    while (is_menu) {
        if (sigint_received) {
            InputEvent quit_event = {};
            quit_event.event = EventType::QUIT;
            return handle_input_menu(quit_event, is_menu, graph);
        }
        auto input = graph->getInput();
        if (handle_input_menu(input, is_menu, graph))
            return 1;
        graph->clear();
        parse_scoreboard();
        show_available_list(graph);
        graph->display();
        if (_name.empty())
            _name = graph->loadName();
    }
    reloads_libs(true, true);
    return 0;
}

int Core::handle_input_lib(InputEvent input)
{
    if (input.event == EventType::QUIT) {
        graph->closeWindow();
        game.reset();
        graph.reset();
        _dl_game.close_lib();
        _dl_graph.close_lib();
        return 1;
    }
    if (input.event == EventType::SWITCH_DISPLAY && !_list_graph.empty()) {
        _index_graph = (_index_graph + 1) % _list_graph.size();
        reloads_libs(true, false);
    }
    if (input.event == EventType::SWITCH_GAME && !_list_games.empty()) {
        _index_game = (_index_game + 1) % _list_games.size();
        reloads_libs(false, true);
    }
    if (input.event == EventType::RESTART_GAME)
        reloads_libs(false, true);
    if (input.event == EventType::CALL_MENU) {
        graph->closeWindow();
        graph.reset();
        _dl_graph.close_lib();
        return launch_menu();
    }
    if (input.event == EventType::ROAR)
        graph->playSound("snake_death");
    return 0;
}

void Core::draw_game()
{
    for (auto &sprite : game->getSprites()) {
        if (sprite.name != "background")
            graph->drawSprite({sprite.x, sprite.y}, sprite.rotation, sprite.size, sprite.name);
        else
            graph->drawBackground(sprite.name);
    }
    for (auto &sound : game->getSounds())
        graph->playSound(sound);
    for (auto &text : game->getTextes())
        graph->drawText({text.x, text.y}, text.size, text.text, RED);
    return;
}

int Core::launch_game()
{
    while (!game->isOver())  {
            if (sigint_received) {
                InputEvent quit_event = {};
                quit_event.event = EventType::QUIT;
                return handle_input_lib(quit_event);
            }
            auto input = graph->getInput();
            if (handle_input_lib(input) == 1)
                return 1;
            graph->clear();
            game->update(input);
            draw_game();
            graph->display();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    store_scoreboard(_name, game->getScore());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    graph->clear();
    graph->drawBackground("background");
    graph->drawText({-1, 8}, 3.0, "GAME OVER", WHITE);
    graph->display();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    graph->closeWindow();
    graph.reset();
    game.reset();
    _dl_game.close_lib();
    _dl_graph.close_lib();
    return 0;
}

int Core::launch_all()
{
    using SignalHandler = void (*)(int);
    SignalHandler previous_handler = std::signal(SIGINT, handle_sigint);
    sigint_received = 0;
    try
    {
        if (_list_graph.empty())
            throw CoreError("No graphical library loaded");
        if (_list_games.empty())
            throw CoreError("No game library loaded");
        while (!sigint_received) {
            if (launch_menu() == 1 || launch_game() == 1) {
                std::signal(SIGINT, previous_handler);
                return 0;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::signal(SIGINT, previous_handler);
        std::cerr << e.what() << '\n';
        return 84;
    }
    std::signal(SIGINT, previous_handler);
    return 0;
}
