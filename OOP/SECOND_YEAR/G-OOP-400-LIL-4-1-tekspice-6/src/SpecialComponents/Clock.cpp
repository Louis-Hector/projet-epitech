/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Clock
*/

#include "Clock.hpp"


namespace nts {
    Clock::Clock()
    {
        _pins = {{},{1}};
    }

    Clock::~Clock()
    {
    }

    void Clock::setState(Tristate newState)
    {
        isNext = true;
        _nextstate = newState;
    }

    void Clock::simulate(std::size_t tick)
    {
        (void)tick;
        if (isNext == true) {
            _state = _nextstate;
            isNext = false;
            return;
        }
        if (_state == Tristate::True)
            _state = Tristate::False;
        else if (_state == Tristate::False)
            _state = Tristate::True;
    }

    nts::Tristate Clock::compute(std::size_t pin)
    {
        if (pin <= 0)
            return Tristate::Undefined;
        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = _state;
        return _pin_value[pin];
    }
}


