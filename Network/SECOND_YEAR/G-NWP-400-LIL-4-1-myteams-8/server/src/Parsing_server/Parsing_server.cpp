/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Parsing_server
*/

#include "Parsing_server.hpp"

Parsing_server::Parsing_server(/* args */)
{
}

Parsing_server::FILE_ERROR::FILE_ERROR(std::string error) : _msg(error)
{
}

const char *Parsing_server::FILE_ERROR::what() const noexcept
{
    return _msg.c_str();
}


int Parsing_server::print_help()
{
    std::cout << "USAGE: ./myteams_server port" << std::endl << std::endl;
    std::cout << "port is the port number on which the server socket listens." << std::endl;
    return 0;
}

void Parsing_server::check_port(char *port)
{
    for (std::size_t i = 0; port[i] != '\0'; i++)
        if (port[i] < '0' || port[i] > '9')
            throw FILE_ERROR("The port : " + std::string(port) + " is not a number");
    int _port = std::stoi(port);
    if (_port < 1 || _port > 65535)
        throw FILE_ERROR("The port " + std::string(port) + " is out of range (port must be between 1 and 65535)");
    return;
}

int Parsing_server::parse_args(int ac, char **av)
{
    try
    {
        if (ac != 2 || av[1] == NULL)
            throw FILE_ERROR("Invalid args");
        if (ac == 2 && std::string(av[1]) == "--help")
            return print_help();
        check_port(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return 84;
    }
    return 0;
}