/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Shell
*/

#include "Shell.hpp"

Shell::Shell()
{
}

bool Shell::parseNumber(const std::string &nb_pizzas, int &number)
{
    if (nb_pizzas.size() < 2 || nb_pizzas[0] != 'x') {
        logger.write_log("the number of pizzas is invalid.");
        logger.write_log("usage: <type> <size> x<number>(; <type> <size> x<number>)*");
        return false;
    }
    if (nb_pizzas[1] < '1' || nb_pizzas[1] > '9') {
        logger.write_log("the number after x must start with [1..9].");
        return false;
    }
    for (std::size_t i = 2; i < nb_pizzas.size(); i++) {
        if (nb_pizzas[i] < '0' || nb_pizzas[i] > '9') {
            logger.write_log("the number after x must contain only digits.");
            return false;
        }
    }
    number = std::atoi(nb_pizzas.c_str() + 1);
    return true;
}

bool Shell::parsePizza(const std::string &pizzas)
{
    std::unordered_map<std::string, PizzaType> type_pizza = {{"regina", PizzaType::Regina}, {"margarita", PizzaType::Margarita}, {"americana", PizzaType::Americana}, {"fantasia", PizzaType::Fantasia}};
    std::unordered_map<std::string, PizzaSize> size_pizza = {{"S", PizzaSize::S}, {"M", PizzaSize::M}, {"L", PizzaSize::L}, {"XL", PizzaSize::XL}, {"XXL", PizzaSize::XXL}};
    std::stringstream ss(pizzas);
    std::string type;
    std::string size;
    std::string number_str;
    std::string extra;
    ss >> type >> size >> number_str;
    if (type.empty() || size.empty() || number_str.empty() || (ss >> extra)) {
        logger.write_log("the command line is invalid.");
        logger.write_log("usage: <type> <size> x<number>(; <type> <size> x<number>)*");
        return false;
    }
    auto new_pizza_type = type_pizza.find(type);
    if (new_pizza_type == type_pizza.end()) {
        logger.write_log("unknown PizzaType.");
        logger.write_log("available types: regina, margarita, americana, fantasia");
        return false;
    }
    auto new_pizza_size = size_pizza.find(size);
    if (new_pizza_size == size_pizza.end()) {
        logger.write_log("unknown PizzaSize.");
        logger.write_log("available sizes: S, M, L, XL, XXL");
        return false;
    }
    int number = 0;
    if (!parseNumber(number_str, number))
        return false;
    Factory factory;
    for (int i = 0; i < number; i++)
        _all_pizza.push_back(factory.createPizza(new_pizza_type->second, new_pizza_size->second));
    return true;
}

void Shell::launch_shell(infos_args_t &infos)
{
    std::string line;
    Reception reception(infos);
    logger.write_log("[Shell] plazza launch with, cooking time multiplier: " + std::to_string(infos.cooking_time_multiplier) + ", number of cooks per kitchen: " + std::to_string(infos.number_of_cooks) + ", time for refill stock (ms): " + std::to_string(infos.time_for_refill_stock));
    while (std::getline(std::cin, line)) {
        _all_pizza.clear();
        if (line.empty()) {
            logger.write_log("the command line is invalid.");
            logger.write_log("usage: <type> <size> x<number>(; <type> <size> x<number>)*");
            continue;
        }
        logger.write_log("[User] " + line);
        if (line == "status") {
            reception.displayStatus();
            continue;
        }
        std::stringstream line_stream(line);
        std::string pizzas;
        bool error = false;
        while (std::getline(line_stream, pizzas, ';')) {
            if (!parsePizza(pizzas)) {
                error = true;
                break;
            }
        }
        if (error)
            continue;
        logger.write_log("[Shell] order contains " + std::to_string(_all_pizza.size()) + " pizzas");
        reception.start_reception(_all_pizza);
    }
    logger.write_log("[Shell] plazza closed");
}