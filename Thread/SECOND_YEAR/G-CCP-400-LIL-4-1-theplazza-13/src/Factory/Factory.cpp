/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Factory
*/

#include "Factory.hpp"

std::unique_ptr<APizza> Factory::createPizza(PizzaType type, PizzaSize size)
{
    switch (type) {
        case PizzaType::Margarita:
            return std::make_unique<Margarita>(size);
        case PizzaType::Regina:
            return std::make_unique<Regina>(size);
        case PizzaType::Americana:
            return std::make_unique<Americana>(size);
        case PizzaType::Fantasia:
            return std::make_unique<Fantasia>(size);
        default:
            return nullptr;
    }
}