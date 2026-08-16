/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Input
*/

#include "Input.hpp"

namespace nts {

    Input::Input()
    {
        _pins = {{},{1}};
    }

    Input::~Input()
    {
    }

    Tristate Input::compute(std::size_t pin)
    {
        if (pin <= 0)
            return Undefined;
        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = _state;
        return _pin_value[pin];
    }

    void Input::simulate(std::size_t tick)
    {
        (void)tick;
        if (isNext == true) {
            _state = _nextstate;
            isNext = false;
        }
        return;
    }

    void Input::setState(Tristate newState)
    {
        isNext = true;
        _nextstate = newState;
    }
}
