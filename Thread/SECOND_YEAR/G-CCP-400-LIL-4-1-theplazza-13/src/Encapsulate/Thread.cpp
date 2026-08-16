/*
** EPITECH PROJECT, 2026
** Thread
** File description:
** Thread
*/

#include "Thread.hpp"

Thread::Thread(void (*function)(void *), void *args) : _thread(function, args)
{
    _state = started;
}

Thread::~Thread()
{
    if (_thread.joinable()) {
        _state = running;
        _thread.join();
    }
    _state = dead;
}

std::thread& Thread::getThread()
{
    return _thread;
}

void Thread::join()
{
    if (_thread.joinable()) {
        _state = running;
        _thread.join();
    }
    _state = dead;
}