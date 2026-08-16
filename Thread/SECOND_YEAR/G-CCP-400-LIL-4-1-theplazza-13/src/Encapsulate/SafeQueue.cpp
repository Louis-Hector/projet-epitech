/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** SafeQueue
*/

#include "SafeQueue.hpp"
#include "ScopedLock.hpp"

SafeQueue::SafeQueue() : _shutdownRequested(false)
{
}

SafeQueue::~SafeQueue()
{
}

void SafeQueue::push(std::unique_ptr<APizza> pizza)
{
    {
        ScopedLock lock(_mutex);
        _queue.push(std::move(pizza));
    }
    _condVar.notify_one(); 
}

std::optional<std::unique_ptr<APizza>> SafeQueue::pop()
{
    _mutex.lock();
    _condVar.wait(_mutex, [this]() {
        return !_queue.empty() || _shutdownRequested;
    });
    if (_queue.empty() && _shutdownRequested) {
        _mutex.unlock();
        return std::nullopt;
    }
    std::unique_ptr<APizza> pizza = std::move(_queue.front());
    _queue.pop();
    _mutex.unlock();
    return pizza;
}

bool SafeQueue::tryPop(std::unique_ptr<APizza> &pizza)
{
    ScopedLock lock(_mutex);

    if (!_queue.empty()) {
        pizza = std::move(_queue.front());
        _queue.pop();
        return true;
    }
    return false;
}

bool SafeQueue::isEmpty(void)
{
    ScopedLock lock(_mutex);

    if (_queue.empty()) {
        return true;
    }
    return false;
}

void SafeQueue::shutdown()
{
    {
        ScopedLock lock(_mutex);
        _shutdownRequested = true;
    }
    _condVar.notify_all(); 
}