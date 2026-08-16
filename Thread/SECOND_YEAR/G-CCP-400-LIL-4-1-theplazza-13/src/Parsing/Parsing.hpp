/*
** EPITECH PROJECT, 2026
** Thread
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <iostream>
#include <exception>
#include "Constant.hpp"

class Parsing
{
private:
    double parsePositiveDouble(const std::string &str);
    int parsePositiveInt(const std::string &str);
public:
    Parsing(/* args */);
    ~Parsing() = default;
    void parse_args(int ac, char **av, infos_args_t &info);
    class ARGS_ERROR : public std::exception {
        private:
            std::string _msg;
        public:
            ARGS_ERROR(std::string error);
            const char *what() const noexcept override;
    };
};

#endif /* !PARSING_HPP_ */
