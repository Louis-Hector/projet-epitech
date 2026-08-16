/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** ScopedLock
*/

#ifndef SCOPEDLOCK_HPP_
#define SCOPEDLOCK_HPP_

#include "Mutex.hpp"

class ScopedLock {
    public:
        ScopedLock(Mutex &mutex);
        ~ScopedLock();
    private:
        Mutex &_mutex;
};

#endif /* !SCOPEDLOCK_HPP_ */
