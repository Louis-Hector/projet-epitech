/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Shell
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Constant.hpp"
#include "APizza.hpp"
#include "IPC.hpp"
#include "Reception.hpp"
#include "Log.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"
#include "Factory.hpp"

class Shell
{
    private:
        std::vector<std::unique_ptr<APizza>> _all_pizza;
    public:
        Shell();
        ~Shell() = default;
        bool parsePizza(const std::string &pizzas);
        bool parseNumber(const std::string &nb_pizzas, int &number);
        void launch_shell(infos_args_t &infos);
};


#endif /* !SHELL_HPP_ */
