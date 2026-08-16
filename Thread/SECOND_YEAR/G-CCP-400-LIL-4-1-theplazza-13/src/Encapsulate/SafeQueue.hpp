/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <queue>
#include <iostream>
#include "Mutex.hpp"
#include "CondVar.hpp"
#include "APizza.hpp"
#include <optional>


class SafeQueue {
    public:
        SafeQueue();
        ~SafeQueue();
        void push(std::unique_ptr<APizza> pizza);
        bool tryPop(std::unique_ptr<APizza> &pizza);
        bool isEmpty(void);
        std::optional<std::unique_ptr<APizza>> pop();
        void shutdown();
    private:
        std::queue<std::unique_ptr<APizza>> _queue;
        Mutex _mutex;
        CondVar _condVar;
        bool _shutdownRequested = false;
};

#endif /* !SAFEQUEUE_HPP_ */
