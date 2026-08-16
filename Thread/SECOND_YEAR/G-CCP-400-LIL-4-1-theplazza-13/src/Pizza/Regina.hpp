/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Regina
*/

#ifndef REGINA_HPP_
#define REGINA_HPP_

#include "APizza.hpp"

class Regina : public APizza
{
private:
    /* data */
public:
    Regina(PizzaSize size);
    std::string getTypeName() const override;
    double getCookingTimeMs(double multiplier) const override;
    std::vector<Ingredient> getIngredients() const override;
};


#endif /* !REGINA_HPP_ */
