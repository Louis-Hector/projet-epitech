/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** APizza
*/

#ifndef APIZZA_HPP_
#define APIZZA_HPP_

#include "IPizza.hpp"

class APizza : public IPizza
{
private:
    /* data */
public:
    APizza(PizzaType pizza_type, PizzaSize _pizza_size);
    ~APizza() = default;
    std::string getSizeName() const override;
    virtual std::string getTypeName() const = 0;
    virtual double getCookingTimeMs(double multiplier) const = 0;
    virtual std::vector<Ingredient> getIngredients() const = 0;
    PizzaSize getSize() const override;
    PizzaType getType() const override;
    void setOrderId(int orderId);
    int getOrderId() const;
protected:
    PizzaType _pizza_type;
    PizzaSize _pizza_size;
    int _orderId;
};


#endif /* !APIZZA_HPP_ */
