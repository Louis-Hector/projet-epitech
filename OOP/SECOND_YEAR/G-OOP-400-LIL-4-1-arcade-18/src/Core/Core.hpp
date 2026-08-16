/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <csignal>
#include "IDisplay.hpp"
#include "Libdl.hpp"
#include "IGame.hpp"

class Core
{
private:
    std::vector<std::string> &_list_graph;
    std::vector<std::string> &_list_games;
    std::size_t _index_game = {0};
    std::size_t _index_graph = {0};
    std::unique_ptr<IDisplay> graph = nullptr;
    std::unique_ptr<IGame> game = nullptr;
    Libdl _dl_graph;
    Libdl _dl_game;
    std::string _name;
    std::vector<std::pair<std::string, int>> _scoreboard;
    static volatile std::sig_atomic_t sigint_received;
    static void handle_sigint(int);
public:
    template <typename T>
    std::unique_ptr<T> recover_lib(const char *path_lib, Libdl &_dl);
    Core(std::vector<std::string> &_parse_libs, std::vector<std::string> &_parse_games);
    ~Core();
    void reloads_libs(bool is_graphical, bool is_game);
    void show_available_list(std::unique_ptr<IDisplay> &graph);
    int handle_input_lib(InputEvent input);
    int handle_input_menu(InputEvent input, bool &is_menu, std::unique_ptr<IDisplay> &graph);
    void draw_game();
    int launch_menu();
    int launch_game();
    int launch_all();
    void parse_scoreboard();
    void store_scoreboard(std::string name_player, int score);
    std::string get_scoreboard_file();
    class CoreError : public std::exception {
        public:
            CoreError(std::string error);
            const char *what() const noexcept override;
        private:
            std::string _msg;
    };
};



#endif /* !CORE_HPP_ */
