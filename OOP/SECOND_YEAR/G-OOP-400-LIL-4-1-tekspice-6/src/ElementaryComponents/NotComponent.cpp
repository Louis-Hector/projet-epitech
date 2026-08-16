/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** NotComponent
*/

#include "NotComponent.hpp"

namespace nts {

    NotComponent::NotComponent()
    {
        _pins = {{1},{2}};
    }

    NotComponent::~NotComponent()
    {
    }

    Tristate NotComponent::compute(std::size_t pin)
    {
        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        Tristate a = getLink(1);
        if (a == True)
            _pin_value[pin] = False;
        else if (a == False)
            _pin_value[pin] = True;
        else
            _pin_value[pin] = Undefined;
        return _pin_value[pin];
    }
}