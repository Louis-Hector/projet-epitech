/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Margarita
*/

#ifndef MARGARITA_HPP_
#define MARGARITA_HPP_

#include "APizza.hpp"

class Margarita : public APizza
{
private:
    /* data */
public:
    Margarita(PizzaSize size);
    std::string getTypeName() const override;
    double getCookingTimeMs(double multiplier) const override;
    std::vector<Ingredient> getIngredients() const override;
};

#endif /* !MARGARITA_HPP_ */
