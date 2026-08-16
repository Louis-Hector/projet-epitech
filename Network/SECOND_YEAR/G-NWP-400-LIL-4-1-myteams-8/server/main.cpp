/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** main
*/

#include "Parsing_server.hpp"
#include "Core.hpp"
#include "LoadSave.hpp"

int main(int ac, char **av)
{
    Parsing_server parse;
    Core core;

    if (parse.parse_args(ac, av) == 84)
        return 84;
    return core.start_serv(std::stoi(av[1]));
}