/*
** EPITECH PROJECT, 2026
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include "IPC.hpp"
#include "ScopedLock.hpp"
#include "Factory.hpp"
#include "IPCMessage.hpp"
#include "SafeQueue.hpp"
#include "Thread.hpp"
#include "Log.hpp"
#include "Stock.hpp"
#include "APizza.hpp"

class Kitchen;

struct CookerArgs {
    SafeQueue *queue;
    double cookingTimeMultiplier;
    Stock *stock;
    int kitchenId;
    int cookerId;
    std::string returnFifoPath;
    Kitchen *kitchen;
};

enum CookerState {
    DO_NOTHING,
    WAITING_INGREDIENTS,
    COOKING_PIZZA
};

struct CookerStatus {
    int id;
    CookerState state;
    int orderId;
    std::string pizzaType;
    std::string pizzaSize;
};

class Kitchen {
    public:
        Kitchen(int id, const std::string &fifoPath, const std::string &returnFifoPath, double cookingTimeMultiplier, int nbCookers, int _timeForRefillStock);
        ~Kitchen();
        void run();

    private:
        static void cookerThreadRoutine(void *args);
        int getPizzasInKitchen();
        void sendStatus();
        void notifyPizzaReceived();
        void notifyPizzaDone();
        bool isKitchenActive();
        void closeKitchen();
        void setCookerStatus(int cookerId, CookerState state, const APizza *pizza);
        std::string getCookerThreadPoolStatus();
        std::string getCookerStateName(CookerState state);
        std::vector<std::unique_ptr<Thread>> _cookersThreadPool;
        std::vector<std::unique_ptr<CookerArgs>> _cookerArgs;
        std::vector<CookerStatus> _cookersStatus;
        Mutex _cookersStatusMutex;
        int _id;
        std::string _fifoPath;
        std::string _returnFifoPath;
        double _cookingTimeMultiplier;
        int _nbCookers;
        int _timeForRefillStock;
        Stock _stock;
        SafeQueue _pizzaQueue;
        Mutex _mutex;
        int _pizzasInKitchen;
        time_t _lastAction;
};

#endif /* !KITCHEN_HPP_ */