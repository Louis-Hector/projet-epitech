/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** XorComponent
*/

#include "XorComponent.hpp"

namespace nts {
    XorComponent::XorComponent()
    {
        _pins = {{1, 2},{3}};
    }

    XorComponent::~XorComponent()
    {
    }

    Tristate XorComponent::compute(std::size_t pin) {

        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        if (pin != 3)
            return Undefined;
        Tristate a = getLink(1);
        Tristate b = getLink(2);
        if ((a == True && b == False) || (a == False && b == True))
            _pin_value[pin] = True;
        else if ((a == True && b == True) || (a == False && b == False))
            _pin_value[pin] = False;
        else
            _pin_value[pin] = Undefined;
        return _pin_value[pin];
    }
}
