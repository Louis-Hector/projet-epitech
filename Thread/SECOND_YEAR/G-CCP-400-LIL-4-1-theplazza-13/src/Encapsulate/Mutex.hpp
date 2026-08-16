/*
** EPITECH PROJECT, 2026
** Thread
** File description:
** AMutex
*/

#ifndef AMUTEX_HPP_
#define AMUTEX_HPP_

#include <stdexcept>
#include <mutex>

class Mutex 
{
private:
    std::mutex _mutex;
public:
    Mutex(/* args */);
    ~Mutex();
    void lock();
    void unlock();
    std::mutex &getMutex();
};


#endif /* !AMUTEX_HPP_ */
