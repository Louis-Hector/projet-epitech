/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Fantasia
*/

#include "Fantasia.hpp"

Fantasia::Fantasia(PizzaSize size) : APizza(PizzaType::Fantasia, size)
{
}

std::string Fantasia::getTypeName() const
{
    return "Fantasia";
}

double Fantasia::getCookingTimeMs(double multiplier) const
{
    return (4000 * multiplier);
}

std::vector<Ingredient> Fantasia::getIngredients() const
{
    return {Dough, Tomato, Eggplant, GoatCheese, ChiefLove};
}