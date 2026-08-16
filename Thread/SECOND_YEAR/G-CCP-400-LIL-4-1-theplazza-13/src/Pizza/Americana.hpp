/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Americana
*/

#ifndef AMERICANA_HPP_
#define AMERICANA_HPP_

#include "APizza.hpp"

class Americana : public APizza
{
private:
public:
    Americana(PizzaSize size);
    std::string getTypeName() const override;
    double getCookingTimeMs(double multiplier) const override;
    std::vector<Ingredient> getIngredients() const override;
};


#endif /* !AMERICANA_HPP_ */
