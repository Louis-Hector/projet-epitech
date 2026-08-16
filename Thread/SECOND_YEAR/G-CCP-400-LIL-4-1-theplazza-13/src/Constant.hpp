/*
** EPITECH PROJECT, 2026
** Thread
** File description:
** Constant
*/

#ifndef CONSTANT_HPP_
#define CONSTANT_HPP_

typedef struct infos_args_s {
    double cooking_time_multiplier;
    int number_of_cooks;
    int time_for_refill_stock;
} infos_args_t;

enum Ingredient {
    Dough,
    Tomato,
    Gruyere,
    Ham,
    Mushrooms,
    Steak,
    Eggplant,
    GoatCheese,
    ChiefLove
};

enum class PizzaType : int {
    None = -1,
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum class PizzaSize : int {
    None = -1,
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

#endif /* !CONSTANT_HPP_ */
