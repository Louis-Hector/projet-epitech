/*
** EPITECH PROJECT, 2026
** Plazza
** File description:
** Condvar
*/

#ifndef CONDVAR_HPP_
#define CONDVAR_HPP_

#include <condition_variable>
#include <functional>
#include "Mutex.hpp"

class CondVar {
    public:
        CondVar();
        ~CondVar();
        void wait(Mutex &mutex);
        void wait(Mutex &mutex, std::function<bool()> predicate);
        void notify_one();
        void notify_all();

    private:
        std::condition_variable _condVar;
};

#endif /* !CONDVAR_HPP_ */