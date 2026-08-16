/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Output
*/

#include "Output.hpp"

namespace nts {

    Output::Output()
    {
        _pins = {{1},{}};
    }

    Output::~Output()
    {
    }

    Tristate Output::compute (std::size_t pin) 
    {
        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = getLink(pin);
        return _pin_value[pin];

    }
}
