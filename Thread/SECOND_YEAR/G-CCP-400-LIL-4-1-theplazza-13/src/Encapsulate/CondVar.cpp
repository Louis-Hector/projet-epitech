/*
** EPITECH PROJECT, 2026
** Plazza
** File description:
** Condvar
*/

#include "CondVar.hpp"

CondVar::CondVar()
{
}

CondVar::~CondVar()
{
}

void CondVar::wait(Mutex &mutex)
{
    std::unique_lock<std::mutex> lock(mutex.getMutex(), std::adopt_lock);

    _condVar.wait(lock);
    lock.release();
}

void CondVar::wait(Mutex &mutex, std::function<bool()> predicate)
{
    std::unique_lock<std::mutex> lock(mutex.getMutex(), std::adopt_lock);

    _condVar.wait(lock, predicate);
    lock.release();
}

void CondVar::notify_one()
{
    _condVar.notify_one();
}

void CondVar::notify_all()
{
    _condVar.notify_all();
}