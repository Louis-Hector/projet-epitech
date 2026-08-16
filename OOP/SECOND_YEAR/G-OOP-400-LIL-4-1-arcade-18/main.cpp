/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** main
*/

#include <iostream>
#include "Parsing.hpp"

int main(int ac, char **av)
{
    Parsing parse;

    if (parse.parse_args(ac, av) == 84)
        return 84;
    Core core(parse._parse_librarys, parse._parse_games);
    return core.launch_all();
}