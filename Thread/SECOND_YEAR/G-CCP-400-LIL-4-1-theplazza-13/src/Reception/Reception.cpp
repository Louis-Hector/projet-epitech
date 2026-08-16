/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Processus.hpp"

Reception::Reception(infos_args_t &infos): _infos(infos), _returnFifoPath("/tmp/plazza_reception"), _returnFifo(nullptr), _nextKitchenId(1), _nextOrderId(1), _listenerThread(nullptr), _listenerRunning(true), _pos_kitchen(0)
{
    _returnFifo = std::make_unique<IPC>(_returnFifoPath);
    _returnFifo->open_mode_file(O_RDWR);
    _listenerThread = std::make_unique<Thread>(&Reception::listener, this);
}

Reception::~Reception()
{
    {
        ScopedLock lock(_listenerMutex);
        _listenerRunning = false;
    }
    if (_listenerThread)
        _listenerThread->join();
    unlink(_returnFifoPath.c_str());
}

void Reception::listener(void *args)
{
    Reception *reception = static_cast<Reception *>(args);
    reception->listenKitchenMessages();
}

void Reception::listenKitchenMessages()
{
    while (true) {
        {
            ScopedLock lock(_listenerMutex);
            if (!_listenerRunning)
                break;
        }
        if (_returnFifo->wait_for_data(100))
            checkKitchenMessages();
    }
}

void Reception::create_new_kitchen()
{
    int new_id;
    {
        ScopedLock lock(_kitchensMutex);
        new_id = _nextKitchenId++;
    }
    std::string kitchenFifoPath = "/tmp/plazza_" + std::to_string(new_id);

    Processus processus;
    pid_t pid = processus.forkProcessus();
    if (processus.isChild()) {
        {
            Kitchen kitchen(new_id, kitchenFifoPath, _returnFifoPath, _infos.cooking_time_multiplier, _infos.number_of_cooks, _infos.time_for_refill_stock);
            kitchen.run();
        }
        std::exit(0);
    }
    {
        ScopedLock lock(_kitchensMutex);
        _active_kitchens.push_back({new_id, pid, kitchenFifoPath, 0});
    }
}

void Reception::start_reception(std::vector<std::unique_ptr<APizza>> &pizzas)
{
    int orderId;
    {
        ScopedLock lock(_ordersMutex);
        orderId = _nextOrderId++;
        _orders.push_back({orderId, static_cast<int>(pizzas.size()), 0, false});
    }
    logger.write_log("[Reception] order " + std::to_string(orderId) + " created with " + std::to_string(pizzas.size()) + " pizza(s)");
    for (std::size_t i = 0; i < pizzas.size();) {
        bool pizza_assigned = false;
        int selectedKitchenId = -1;
        std::string selectedFifoPath;
        {
            ScopedLock lock(_kitchensMutex);
            for (std::size_t i = 0; i < _active_kitchens.size(); i++) {
                auto &kitchen = _active_kitchens[(_pos_kitchen + i) % _active_kitchens.size()];
                if (kitchen.pizzas_in_progress < _infos.number_of_cooks * 2) {
                    kitchen.pizzas_in_progress++;
                    selectedKitchenId = kitchen.id;
                    selectedFifoPath = kitchen.fifo_path;
                    pizza_assigned = true;
                    _pos_kitchen = (_pos_kitchen + 1) % _active_kitchens.size();
                    break;
                }
            }
        }
        if (!pizza_assigned) {
            create_new_kitchen();
            continue;
        }
        pizzas[i]->setOrderId(orderId);
        IPC fifo_target(selectedFifoPath);
        fifo_target.open_mode_file(O_WRONLY);

        IPCMessage pizza_send(IPC_PIZZA_SEND, pizzas[i]->getOrderId(), selectedKitchenId, pizzas[i]->getType(), pizzas[i]->getSize());
        fifo_target.writeMessage(pizza_send.pack());
        logger.write_log("[Reception] pizza id: " + std::to_string(i) + ", type: " + pizzas[i]->getTypeName() + ", size: " + pizzas[i]->getSizeName() + ", from order: " + std::to_string(pizzas[i]->getOrderId()) + " send to kitchen " + std::to_string(selectedKitchenId));
        i++;
    }
}

void Reception::handleKitchenMessage(const IPCMessage &message)
{
    if (message.getStatus() == IPC_PIZZA_DONE) {
        int kitchenId = message.getKitchenId();
        int orderId = message.getOrderId();
        {
            ScopedLock lock(_kitchensMutex);
            for (auto &kitchen : _active_kitchens) {
                if (kitchen.id == kitchenId) {
                    if (kitchen.pizzas_in_progress > 0)
                        kitchen.pizzas_in_progress--;
                    logger.write_log("[Reception] pizza from order " + std::to_string(orderId) + ", done by kitchen " + std::to_string(kitchenId) + ", " + std::to_string(kitchen.pizzas_in_progress) + " pizza(s) remaining");
                    break;
                }
            }
        }
        {
            ScopedLock lock(_ordersMutex);
            for (auto &order : _orders) {
                if (order.id == orderId) {
                    if (order.isOrderCompleted)
                        return;
                    order.numberPizzasDone++;
                    logger.write_log("[Reception] order " + std::to_string(orderId) + " progress: " + std::to_string(order.numberPizzasDone) + "/" + std::to_string(order.numberPizzasOrdered));
                    if (order.numberPizzasDone == order.numberPizzasOrdered && !order.isOrderCompleted) {
                        order.isOrderCompleted = true;
                        logger.write_log("[Reception] order " + std::to_string(orderId) + " is ready");
                    }
                    break;
                }
            }
        }
        return;
    }
    if (message.getStatus() == IPC_KITCHEN_CLOSED) {
        int kitchenId = message.getKitchenId();
        ScopedLock lock(_kitchensMutex);
        for (auto kitchen = _active_kitchens.begin(); kitchen != _active_kitchens.end(); kitchen++) {
            if (kitchen->id == kitchenId) {
                Processus::waitPid(kitchen->pid);
                logger.write_log("[Reception] kitchen " + std::to_string(kitchenId) + " closed");
                _active_kitchens.erase(kitchen);
                break;
            }
        }
        return;
    }
}

void Reception::checkKitchenMessages()
{
    try {
        PackedIPCMessage packed = _returnFifo->readMessage();
        IPCMessage message;
        message.unpack(packed);
        handleKitchenMessage(message);
    } catch (const std::exception &) {
        logger.write_log("[Reception] invalid IPC message");
    }
}

void Reception::displayStatus()
{
    std::vector<KitchenInfo> allKitchensInfo;
    {
        ScopedLock lock(_kitchensMutex);
        if (_active_kitchens.empty()) {
            logger.write_log("[Status] no active kitchen");
            return;
        }
        allKitchensInfo = _active_kitchens;
    }
    logger.write_log("[Status] active kitchen(s): " + std::to_string(allKitchensInfo.size()));
    for (auto &kitchen : allKitchensInfo) {
        try {
            IPC fifo_target(kitchen.fifo_path);
            fifo_target.open_mode_file(O_RDWR);
            IPCMessage status(IPC_STATUS, -1, kitchen.id, PizzaType::None, PizzaSize::None);
            fifo_target.writeMessage(status.pack());
        } catch (const std::exception &) {
            logger.write_log("[Status] fail to get status from kitchen " + std::to_string(kitchen.id));
        }
    }
}