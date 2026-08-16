/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** APizza
*/

#include "APizza.hpp"

APizza::APizza(PizzaType pizza_type, PizzaSize pizza_size) : _pizza_type(pizza_type), _pizza_size(pizza_size), _orderId(-1)
{
}

std::string APizza::getSizeName() const
{
    switch (_pizza_size) {
        case PizzaSize::S:
            return "S";
        case PizzaSize::M:
            return "M";
        case PizzaSize::L:
            return "L";
        case PizzaSize::XL:
            return "XL";
        case PizzaSize::XXL:
            return "XXL";
        default:
            return "Unknown size";
    }
}


PizzaSize APizza::getSize() const
{
    return _pizza_size;
}

PizzaType APizza::getType() const
{
    return _pizza_type;
}

void APizza::setOrderId(int orderId)
{
    _orderId = orderId;
}

int APizza::getOrderId() const
{
    return _orderId;
}