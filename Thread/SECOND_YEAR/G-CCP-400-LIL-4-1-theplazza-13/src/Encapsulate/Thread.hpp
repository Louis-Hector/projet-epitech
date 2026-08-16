/*
** EPITECH PROJECT, 2026
** Thread
** File description:
** Thread
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <stdexcept>
#include <thread>

enum State_t {
    started,
    running,
    dead
};

class Thread
{
private:
    std::thread _thread;
    State_t _state;
public:
    Thread(void (*function)(void *), void *args);
    ~Thread();
    std::thread &getThread();
    void join();
};

#endif /* !THREAD_HPP_ */
