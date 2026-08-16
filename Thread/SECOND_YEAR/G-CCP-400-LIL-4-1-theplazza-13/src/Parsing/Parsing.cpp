/*
** EPITECH PROJECT, 2026
** Thread
** File description:
** Parsing
*/

#include "Parsing.hpp"

Parsing::Parsing(/* args */)
{
}

Parsing::ARGS_ERROR::ARGS_ERROR(std::string error) : _msg(error)
{    
}

const char *Parsing::ARGS_ERROR::what() const noexcept
{
    return _msg.c_str();
}

double Parsing::parsePositiveDouble(const std::string &str)
{
    std::size_t pos = 0;
    double value = 0;

    try {
        value = std::stod(str, &pos);
    } catch (const std::exception &) {
        throw ARGS_ERROR("'" + str + "': Invalid positive double\nUsage: ./plazza <cooking time multiplier> <number of cooks per kitchen> <time in milliseconds to replace ingredients>");
    }
    if (pos != str.size() || value <= 0)
        throw ARGS_ERROR("'" + str + "': Invalid positive double\nUsage: ./plazza <cooking time multiplier> <number of cooks per kitchen> <time in milliseconds to replace ingredients>");
    return value;
}

int Parsing::parsePositiveInt(const std::string &str)
{
    std::size_t pos = 0;
    int value = 0;

    try {
        value = std::stoi(str, &pos);
    } catch (const std::exception &) {
        throw ARGS_ERROR("'" + str + "': Invalid positive integer\nUsage: ./plazza <cooking time multiplier> <number of cooks per kitchen> <time in milliseconds to replace ingredients>");
    }
    if (pos != str.size() || value <= 0)
        throw ARGS_ERROR("'" + str + "': Invalid positive integer\nUsage: ./plazza <cooking time multiplier> <number of cooks per kitchen> <time in milliseconds to replace ingredients>");
    return value;
}

void Parsing::parse_args(int ac, char **av, infos_args_t &info)
{
    if (ac != 4)
        throw ARGS_ERROR("Number of arguments is invalid\nUsage: ./plazza <cooking time multiplier> <number of cooks per kitchen> <time in milliseconds to replace ingredients>");
    info.cooking_time_multiplier = parsePositiveDouble(av[1]);
    info.number_of_cooks = parsePositiveInt(av[2]);
    info.time_for_refill_stock = parsePositiveInt(av[3]);
}