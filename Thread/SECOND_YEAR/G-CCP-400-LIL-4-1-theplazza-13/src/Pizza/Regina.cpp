/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Regina
*/

#include "Regina.hpp"

Regina::Regina(PizzaSize size) : APizza(PizzaType::Regina, size)
{
}

std::string Regina::getTypeName() const
{
    return "Regina";
}

double Regina::getCookingTimeMs(double multiplier) const
{
    return (2000 * multiplier);
}

std::vector<Ingredient> Regina::getIngredients() const
{
    return {Dough, Tomato, Gruyere, Ham, Mushrooms};
}
