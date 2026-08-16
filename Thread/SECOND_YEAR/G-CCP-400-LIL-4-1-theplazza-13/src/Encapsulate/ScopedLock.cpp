/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** ScopedLock
*/

#include "ScopedLock.hpp"

ScopedLock::ScopedLock(Mutex &mutex) : _mutex(mutex)
{
    _mutex.lock();
}

ScopedLock::~ScopedLock()
{
    _mutex.unlock();
}
