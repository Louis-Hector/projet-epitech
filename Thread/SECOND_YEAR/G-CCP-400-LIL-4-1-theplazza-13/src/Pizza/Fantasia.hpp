/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Fantasia
*/

#ifndef FANTASIA_HPP_
#define FANTASIA_HPP_

#include "APizza.hpp"

class Fantasia : public APizza
{
private:
public:
    Fantasia(PizzaSize size);
    std::string getTypeName() const override;
    double getCookingTimeMs(double multiplier) const override;
    std::vector<Ingredient> getIngredients() const override;
};


#endif /* !FANTASIA_HPP_ */
