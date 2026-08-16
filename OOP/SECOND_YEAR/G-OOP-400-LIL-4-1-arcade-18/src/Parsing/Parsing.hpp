/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include "IDisplay.hpp"
#include "Libdl.hpp"
#include "IGame.hpp"
#include "ILib.hpp"
#include "Core.hpp"

class Parsing
{
private:
public:
    Parsing(/* args */);
    std::vector<std::string> _parse_games = {};
    std::vector<std::string> _parse_librarys = {};
    int parse_args(int ac, char **av);
    void check_lib(char *lib);
    void open_folder_lib(char *first_args);
    bool can_launch_graphic();
    class FILE_ERROR : public std::exception {
        public:
            const char *what() const noexcept override;
            FILE_ERROR(std::string msg);
        private:
            std::string _error;
    };
};

#endif /* !PARSING_HPP_ */
