/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** IPCMessage
*/

#ifndef IPCMESSAGE_HPP_
#define IPCMESSAGE_HPP_

#include <string>
#include <sstream>
#include "Constant.hpp"
#include <iostream>
#include <vector>

enum IPCMessageStatus {
    NONE = -1,
    IPC_STATUS = 0,
    IPC_PIZZA_SEND = 1,
    IPC_PIZZA_DONE = 2,
    IPC_KITCHEN_CLOSED = 3
};

struct PackedIPCMessage {
    int status;
    int orderId;
    int kitchenId;
    int pizzaType;
    int pizzaSize;
};

class IPCMessage
{
    private:
        IPCMessageStatus _status;
        int _orderId;
        int _kitchenId;
        PizzaType _pizzaType;
        PizzaSize _pizzaSize;
    public:
        IPCMessage();
        IPCMessage(IPCMessageStatus status, int orderId, int kitchenId, PizzaType pizzaType, PizzaSize pizzaSize);
        ~IPCMessage() = default;
        PackedIPCMessage pack() const;
        void unpack(const PackedIPCMessage &packed);
        IPCMessageStatus getStatus() const;
        int getOrderId() const;
        int getKitchenId() const;
        PizzaType getPizzaType() const;
        PizzaSize getPizzaSize() const;
};

#endif /* !IPCMESSAGE_HPP_ */
