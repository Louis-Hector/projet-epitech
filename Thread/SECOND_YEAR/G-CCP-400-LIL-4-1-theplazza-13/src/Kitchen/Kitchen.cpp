/*
** EPITECH PROJECT, 2026
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(int id, const std::string &fifoPath, const std::string &returnFifoPath, double cookingTimeMultiplier, int nbCookers, int timeForRefillStock): _id(id), _fifoPath(fifoPath), _returnFifoPath(returnFifoPath), _cookingTimeMultiplier(cookingTimeMultiplier), _nbCookers(nbCookers), _stock(timeForRefillStock), _pizzasInKitchen(0), _lastAction(std::time(nullptr))
{
    logger.write_log("[Kitchen " + std::to_string(_id) + "] created with FIFO " + _fifoPath);
    for (int i = 0; i < _nbCookers; i++) {
        _cookersStatus.push_back({i, DO_NOTHING, -1, "-", "-"});
    }
    for (int i = 0; i < _nbCookers; i++) {
        _cookerArgs.push_back(std::make_unique<CookerArgs>(CookerArgs{&_pizzaQueue, _cookingTimeMultiplier, &_stock, _id, i, _returnFifoPath, this}));
        _cookersThreadPool.push_back(std::make_unique<Thread>(&Kitchen::cookerThreadRoutine, _cookerArgs.back().get()));
    }
}

Kitchen::~Kitchen()
{
    logger.write_log("[Kitchen " + std::to_string(_id) + "] deleted");
    _pizzaQueue.shutdown();
    for (auto &cooker : _cookersThreadPool)
        cooker->join();
    unlink(_fifoPath.c_str());
}

std::string Kitchen::getCookerStateName(CookerState state)
{
    if (state == DO_NOTHING)
        return "DO NOTHING";
    if (state == WAITING_INGREDIENTS)
        return "WAITING INGREDIENTS";
    if (state == COOKING_PIZZA)
        return "COOKING PIZZA";
    return "UNKNOWN";
}

void Kitchen::setCookerStatus(int cookerId, CookerState state, const APizza *pizza)
{
    ScopedLock lock(_cookersStatusMutex);
    if (cookerId < 0 || cookerId >= static_cast<int>(_cookersStatus.size()))
        return;
    _cookersStatus[cookerId].state = state;
    if (pizza == nullptr) {
        _cookersStatus[cookerId].orderId = -1;
        _cookersStatus[cookerId].pizzaType = "-";
        _cookersStatus[cookerId].pizzaSize = "-";
        return;
    }
    _cookersStatus[cookerId].orderId = pizza->getOrderId();
    _cookersStatus[cookerId].pizzaType = pizza->getTypeName();
    _cookersStatus[cookerId].pizzaSize = pizza->getSizeName();
}

void Kitchen::cookerThreadRoutine(void *args)
{
    CookerArgs *cookArgs = static_cast<CookerArgs *>(args);
    SafeQueue *queue = cookArgs->queue;
    while (true) {
        std::optional<std::unique_ptr<APizza>> opt_pizza = queue->pop();
        if (!opt_pizza.has_value())
            break;
        std::unique_ptr<APizza> pizza = std::move(opt_pizza.value());
        cookArgs->kitchen->setCookerStatus(cookArgs->cookerId, WAITING_INGREDIENTS, pizza.get());
        logger.write_log("[Cooker] " + std::to_string(cookArgs->cookerId) + " from kitchen " + std::to_string(cookArgs->kitchenId) + ", checking ingredients for pizza " + pizza->getTypeName() + " from order " + std::to_string(pizza->getOrderId()));
        if (!cookArgs->stock->waitAndUseIngredients(pizza->getIngredients())) {
            cookArgs->kitchen->setCookerStatus(cookArgs->cookerId, DO_NOTHING, nullptr);
            break;
        }
        cookArgs->kitchen->setCookerStatus(cookArgs->cookerId, COOKING_PIZZA, &(*pizza));
        logger.write_log("[Cooker] " + std::to_string(cookArgs->cookerId) + " from kitchen " + std::to_string(cookArgs->kitchenId) + ", starting to cook pizza type: " + pizza->getTypeName() + ", size: " + pizza->getSizeName() + ", cookingTime: " + std::to_string(pizza->getCookingTimeMs(cookArgs->cookingTimeMultiplier)) + " from order " + std::to_string(pizza->getOrderId()));
        usleep(pizza->getCookingTimeMs(cookArgs->cookingTimeMultiplier) * 1000);
        logger.write_log("[Cooker] " + std::to_string(cookArgs->cookerId) + " from kitchen " + std::to_string(cookArgs->kitchenId) + ", pizza type: " + pizza->getTypeName() + ", size: " + pizza->getSizeName() + " from order " + std::to_string(pizza->getOrderId()) + " is done!");
        IPC returnFifo(cookArgs->returnFifoPath);
        returnFifo.open_mode_file(O_WRONLY);
        IPCMessage pizza_done(IPC_PIZZA_DONE, pizza->getOrderId(), cookArgs->kitchenId, pizza->getType(), pizza->getSize());
        returnFifo.writeMessage(pizza_done.pack());
        cookArgs->kitchen->notifyPizzaDone();
        cookArgs->kitchen->setCookerStatus(cookArgs->cookerId, DO_NOTHING, nullptr);
    }
}

void Kitchen::run()
{
    IPC kitchen_fifo(_fifoPath);
    kitchen_fifo.open_mode_file(O_RDWR);
    while (true) {
        if (kitchen_fifo.wait_for_data(100)) {
            try {
                PackedIPCMessage packed = kitchen_fifo.readMessage();
                IPCMessage message;
                message.unpack(packed);
                if (message.getStatus() == IPC_STATUS) {
                    sendStatus();
                    continue;
                }
                if (message.getStatus() != IPC_PIZZA_SEND)
                    continue;
                Factory factory;
                std::unique_ptr<APizza> pizza = factory.createPizza(message.getPizzaType(), message.getPizzaSize());
                if (!pizza)
                    continue;
                pizza->setOrderId(message.getOrderId());
                logger.write_log("[Kitchen " + std::to_string(_id) + "] pizza received " "type: " + pizza->getTypeName() + ", size: " + pizza->getSizeName() + " from order: " + std::to_string(pizza->getOrderId()) + " ready to be cooked");
                notifyPizzaReceived();
                _pizzaQueue.push(std::move(pizza));
            } catch (const std::exception &e) {
                logger.write_log("[Kitchen " + std::to_string(_id) + "] error while reading order: " + std::string(e.what()));
            }
        }
        if (!isKitchenActive()) {
            closeKitchen();
            break;
        }
    }
}

std::string Kitchen::getCookerThreadPoolStatus()
{
    ScopedLock lock(_cookersStatusMutex);
    std::string cookers_status = "[";
    for (std::size_t i = 0; i < _cookersStatus.size(); i++) {
        cookers_status += "{";
        const CookerStatus &cooker = _cookersStatus[i];
        cookers_status += "Cooker " + std::to_string(cooker.id) + ": " + getCookerStateName(cooker.state);
        if (cooker.orderId != -1 && getCookerStateName(cooker.state) != getCookerStateName(DO_NOTHING)) {
            cookers_status += ", order: " + std::to_string(cooker.orderId) + ", pizza: " + cooker.pizzaType + ", size: " + cooker.pizzaSize;
        }
        cookers_status += "}";
        if (i + 1 < _cookersStatus.size())
            cookers_status += ", ";
    }
    cookers_status += "]";
    return cookers_status;
}

int Kitchen::getPizzasInKitchen()
{
    ScopedLock lock(_mutex);
    return _pizzasInKitchen;
}

void Kitchen::sendStatus()
{
    logger.write_log("[Status] kitchen " + std::to_string(_id) + ":\n\tInfo: fifo: " + _fifoPath + ", pizza(s) in kitchen: " + std::to_string(getPizzasInKitchen()) + ", capacity: " + std::to_string(_nbCookers * 2) + "\n\tStock: " + _stock.pack() + "\n\tCookers: " + getCookerThreadPoolStatus());
}

void Kitchen::notifyPizzaReceived()
{
    ScopedLock lock(_mutex);
    _pizzasInKitchen++;
    _lastAction = std::time(nullptr);
}

void Kitchen::notifyPizzaDone()
{
    ScopedLock lock(_mutex);
    if (_pizzasInKitchen > 0)
        _pizzasInKitchen--;
    _lastAction = std::time(nullptr);
}

bool Kitchen::isKitchenActive()
{
    ScopedLock lock(_mutex);
    if (_pizzasInKitchen == 0 && std::time(nullptr) - _lastAction >= 5)
        return false;
    return true;
}

void Kitchen::closeKitchen()
{
    IPC returnFifo(_returnFifoPath);
    returnFifo.open_mode_file(O_WRONLY);
    IPCMessage kitchen_close(IPC_KITCHEN_CLOSED, -1, _id, PizzaType::None, PizzaSize::None);
    returnFifo.writeMessage(kitchen_close.pack());
}