/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Gate4069INVERTER
*/

#include "Gate4069INVERTER.hpp"

namespace nts {

    Gate4069INVERTER::Gate4069INVERTER()
    {
        _pins = {{1, 3, 5, 9, 11, 13}, {2, 4, 6, 8, 10, 12}};
    }

    Gate4069INVERTER::~Gate4069INVERTER()
    {
    }

    nts::Tristate Gate4069INVERTER::comInverter(std::size_t pin)
    {
        auto s1 = getLink(pin);

        if (s1 == True)
            return False;
        else if (s1 == False)
            return True;
        else
            return Undefined;
    }

    nts::Tristate Gate4069INVERTER::compute(std::size_t pin)
    {
        std::map<std::size_t, std::size_t> output = 
        {{2, 1}, {4, 3}, {6, 5}, {8, 9}, {10, 11}, {12, 13}};

        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        auto element = output.find(pin);
        if (element != output.end())
            _pin_value[pin] = comInverter(element->second);
        else
            _pin_value[pin] = nts::Undefined;
        return _pin_value[pin];
    }
}