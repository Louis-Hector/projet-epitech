/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** IPizza
*/

#ifndef IPIZZA_HPP_
#define IPIZZA_HPP_

#include <string>
#include <vector>
#include "Constant.hpp"

class IPizza
{
private:
    /* data */
public:
    virtual ~IPizza() = default;
    //virtual void pack() = 0;
    //virtual void unpack() = 0;
    virtual std::string getSizeName() const = 0;
    virtual std::string getTypeName() const = 0;
    virtual double getCookingTimeMs(double multiplier) const = 0;
    virtual std::vector<Ingredient> getIngredients() const = 0;
    virtual PizzaSize getSize() const = 0;
    virtual PizzaType getType() const = 0;
};


#endif /* !IPIZZA_HPP_ */
