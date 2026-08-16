/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Americana
*/

#include "Americana.hpp"

Americana::Americana(PizzaSize size) : APizza(PizzaType::Americana, size)
{
}

std::string Americana::getTypeName() const
{
    return "Americana";
}

double Americana::getCookingTimeMs(double multiplier) const
{
    return (2000 * multiplier);
}

std::vector<Ingredient> Americana::getIngredients() const
{
    return {Dough, Tomato, Gruyere, Steak};
}
