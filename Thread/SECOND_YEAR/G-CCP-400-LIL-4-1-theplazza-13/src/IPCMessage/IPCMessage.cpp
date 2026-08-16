/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** IPCMessage
*/

#include "IPCMessage.hpp"

IPCMessage::IPCMessage() : _status(IPCMessageStatus::NONE), _orderId(-1), _kitchenId(-1), _pizzaType(PizzaType::None), _pizzaSize(PizzaSize::None)
{
}

IPCMessage::IPCMessage(IPCMessageStatus status, int orderId, int kitchenId, PizzaType pizzaType, PizzaSize pizzaSize) : _status(status), _orderId(orderId), _kitchenId(kitchenId), _pizzaType(pizzaType), _pizzaSize(pizzaSize)
{
}

PackedIPCMessage IPCMessage::pack() const
{
    return PackedIPCMessage {static_cast<int>(_status), _orderId, _kitchenId, static_cast<int>(_pizzaType), static_cast<int>(_pizzaSize)};
}

void IPCMessage::unpack(const PackedIPCMessage &packed)
{
    _status = static_cast<IPCMessageStatus>(packed.status);
    _orderId = packed.orderId;
    _kitchenId = packed.kitchenId;
    _pizzaType = static_cast<PizzaType>(packed.pizzaType);
    _pizzaSize = static_cast<PizzaSize>(packed.pizzaSize);
}

IPCMessageStatus IPCMessage::getStatus() const
{
    return _status;
}

int IPCMessage::getOrderId() const
{
    return _orderId;
}

int IPCMessage::getKitchenId() const
{
    return _kitchenId;
}

PizzaType IPCMessage::getPizzaType() const
{
    return _pizzaType;
}

PizzaSize IPCMessage::getPizzaSize() const
{
    return _pizzaSize;
}