/*
** EPITECH PROJECT, 2026
** theplazza
** File description:
** Mutex
*/

#include "Mutex.hpp"

Mutex::Mutex(/* args */)
{
}

Mutex::~Mutex()
{
}

void Mutex::lock()
{
    _mutex.lock();
}

void Mutex::unlock()
{   
    _mutex.unlock();
}

std::mutex &Mutex::getMutex()
{
    return _mutex;
}