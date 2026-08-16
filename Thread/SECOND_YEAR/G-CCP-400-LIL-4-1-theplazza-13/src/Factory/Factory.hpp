/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <memory>
#include "APizza.hpp"
#include "Constant.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"

class Factory
{
    private:
    public:
        static std::unique_ptr<APizza> createPizza(PizzaType type, PizzaSize size);
};


#endif /* !FACTORY_HPP_ */
