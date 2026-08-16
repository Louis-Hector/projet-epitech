/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include "IComponent.hpp"
#include "Circuit.hpp"
#include "Factory.hpp"
#include <fstream>

class Parsing
{
private:
    std::ifstream _file;
    Factory _factory;
    int nb_component {};
public:
    Parsing() = default;
    ~Parsing() = default;
    int launch_nts(int ac, char **av);
    void open_file(char *file);
    void read_file(Circuit &circuit);
    void recover_chips(const std::vector<std::string> &_line, Circuit &circuit);
    void recover_links(const std::vector<std::string> &_line, Circuit &circuit);
    class FILE_ERROR : public std::exception
    {
        private:
            std::string _error;
        public:
            FILE_ERROR(std::string msg);
            const char *what() const noexcept override;
    };
};

#endif /* !Parsing_HPP_ */