/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Stock
*/

#include "Stock.hpp"
#include "ScopedLock.hpp"
#include <unistd.h>
#include "Log.hpp"

Stock::Stock(int time_for_refill_stock) : _refillThread(nullptr), _time_for_refill_stock(time_for_refill_stock), _isRefilling(true)
{
    init_stock();
    _refillThread = std::make_unique<Thread>(&Stock::refill, this);
}

Stock::~Stock()
{
    {
        ScopedLock lock(_mutex);
        _isRefilling = false;
    }
    _condVar.notify_all();
    if (_refillThread)
        _refillThread->join();
}

void Stock::init_stock()
{
    _ingredients[Dough] = 5;
    _ingredients[Tomato] = 5;
    _ingredients[Gruyere] = 5;
    _ingredients[Ham] = 5;
    _ingredients[Mushrooms] = 5;
    _ingredients[Steak] = 5;
    _ingredients[Eggplant] = 5;
    _ingredients[GoatCheese] = 5;
    _ingredients[ChiefLove] = 5;
}

bool Stock::hasIngredients(const std::vector<Ingredient> &ingredients)
{
    for (Ingredient ingredient : ingredients) {
        if (_ingredients[ingredient] == 0)
            return false;
    }
    return true;
}

void Stock::useIngredients(const std::vector<Ingredient> &ingredients)
{
    for (Ingredient ingredient : ingredients)
        _ingredients[ingredient]--;
}

bool Stock::waitAndUseIngredients(const std::vector<Ingredient> &ingredients)
{
    _mutex.lock();
    while (_isRefilling && !hasIngredients(ingredients))
        _condVar.wait(_mutex);
    if (!_isRefilling) {
        _mutex.unlock();
        return false;
    }
    useIngredients(ingredients);
    _mutex.unlock();
    return true;
}

void Stock::refill(void *args)
{
    Stock *stock = static_cast<Stock *>(args);
    stock->refillLoop();
}

void Stock::refillLoop()
{
    while (true) {
        usleep(_time_for_refill_stock * 1000);
        {
            ScopedLock lock(_mutex);
            if (!_isRefilling)
                break;
            for (auto &ingredient : _ingredients) {
                if (ingredient.second < std::numeric_limits<std::size_t>::max())
                    ingredient.second++;
            }
        }
        _condVar.notify_all();
    }
}

std::string Stock::pack()
{
    ScopedLock lock(_mutex);
    return "{Dough:" + std::to_string(_ingredients[Dough]) + ", Tomato:" + std::to_string(_ingredients[Tomato]) + ", Gruyere:" + std::to_string(_ingredients[Gruyere]) + ", Ham:" + std::to_string(_ingredients[Ham]) + ", Mushrooms:" + std::to_string(_ingredients[Mushrooms]) + ", Steak:" + std::to_string(_ingredients[Steak]) + ", Eggplant:" + std::to_string(_ingredients[Eggplant]) + ", GoatCheese:" + std::to_string(_ingredients[GoatCheese]) + ", ChiefLove:" + std::to_string(_ingredients[ChiefLove]) + "}";
}