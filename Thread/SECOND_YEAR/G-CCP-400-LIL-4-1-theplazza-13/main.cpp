/*
** EPITECH PROJECT, 2026
** Thread
** File description:
** main
*/

#include <iostream>
#include "Parsing.hpp"
#include "Log.hpp"
#include "Constant.hpp"
#include "Shell.hpp"

int main(int ac, char **av)
{
    Parsing parse;

    try
    {
        infos_args_t info;
        parse.parse_args(ac, av, info);
        Shell shell;
        shell.launch_shell(info);
    }
    catch(const IPC::ERROR_IPC &e) {
        std::cerr << "Error system : " + std::string(e.what()) << std::endl;
        return 84;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}