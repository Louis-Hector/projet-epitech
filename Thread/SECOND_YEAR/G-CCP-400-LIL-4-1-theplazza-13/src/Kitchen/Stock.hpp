/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Stock
*/

#ifndef STOCK_HPP_
#define STOCK_HPP_

#include "Constant.hpp"
#include <vector>
#include <map>
#include "Mutex.hpp"
#include "Thread.hpp"
#include "CondVar.hpp"

class Stock {
    public:
        Stock(int time_for_refill_stock);
        ~Stock();
        bool waitAndUseIngredients(const std::vector<Ingredient> &ingredients);
        std::string pack();
    private:
        void init_stock();
        static void refill(void *args);
        void refillLoop();
        bool hasIngredients(const std::vector<Ingredient> &ingredients);
        void useIngredients(const std::vector<Ingredient> &ingredients);
        std::map<Ingredient, size_t> _ingredients;
        CondVar _condVar;
        Mutex _mutex;
        std::unique_ptr<Thread> _refillThread;
        int _time_for_refill_stock;
        bool _isRefilling;
};

#endif /* !STOCK_HPP_ */
