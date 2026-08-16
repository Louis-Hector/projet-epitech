/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Parsing_server
*/

#ifndef PARSING_SERVER_HPP_
#define PARSING_SERVER_HPP_

#include <iostream>
#include <string>

class Parsing_server
{
private:
public:
    Parsing_server(/* args */);
    int parse_args(int ac, char **av);
    int print_help();
    void check_port(char *port);
    class FILE_ERROR : public std::exception {
        public:
            FILE_ERROR(std::string error);
            const char *what() const noexcept override;
        private:
            std::string _msg;
    };
};

#endif /* !_server_SERVER_HPP_ */
