/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <vector>
#include <sys/wait.h>
#include <iostream>
#include "Log.hpp"
#include "IPC.hpp"
#include "Thread.hpp"
#include "IPCMessage.hpp"
#include "Shell.hpp"
#include "Kitchen.hpp"
#include "ScopedLock.hpp"
#include "APizza.hpp"

struct KitchenInfo {
    int id;
    pid_t pid;
    std::string fifo_path;
    int pizzas_in_progress;
};

struct OrderInfo {
    int id;
    int numberPizzasOrdered;
    int numberPizzasDone;
    bool isOrderCompleted;
};

class Reception
{
    private:
        infos_args_t &_infos;
        std::string _returnFifoPath;
        std::unique_ptr<IPC> _returnFifo;
        std::vector<KitchenInfo> _active_kitchens;
        int _nextKitchenId;
        std::vector<OrderInfo> _orders;
        int _nextOrderId;
        Mutex _ordersMutex;
        Mutex _listenerMutex;
        Mutex _kitchensMutex;
        std::unique_ptr<Thread> _listenerThread;
        bool _listenerRunning;
        std::size_t _pos_kitchen;
        static void listener(void *args);
        void listenKitchenMessages();
        void handleKitchenMessage(const IPCMessage &message);
    public:
        Reception(infos_args_t &infos);
        ~Reception();
        void create_new_kitchen();
        void start_reception(std::vector<std::unique_ptr<APizza>> &Pizzas);
        void checkKitchenMessages();
        void displayStatus();
};

#endif /* !RECEPTION_HPP_ */
