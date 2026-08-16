/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Margarita
*/

#include "Margarita.hpp"

Margarita::Margarita(PizzaSize size) : APizza(PizzaType::Margarita, size)
{
}

std::string Margarita::getTypeName() const
{
    return "Margarita";
}

double Margarita::getCookingTimeMs(double multiplier) const
{
    return (1000 * multiplier);
}

std::vector<Ingredient> Margarita::getIngredients() const
{
    return {Dough, Tomato, Gruyere};
}