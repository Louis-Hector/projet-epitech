/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Gate4071OR
*/

#include "Gate4071OR.hpp"

namespace nts {

    Gate4071OR::Gate4071OR()
    {
        _pins = {{1, 2, 5, 6, 8, 9, 12, 13}, {3, 4, 10, 11}};
    }

    Gate4071OR::~Gate4071OR()
    {
    }

    nts::Tristate Gate4071OR::comOr(std::size_t pin1, std::size_t pin2)
    {
        auto s1 = getLink(pin1);
        auto s2 = getLink(pin2);
        if (s1 == True || s2 == True)
            return True;
        else if (s1 == False && s2 == False)
            return False;
        else
            return Undefined;
    }

    nts::Tristate Gate4071OR::compute(std::size_t pin)
    {
        std::map<std::size_t, std::pair<std::size_t, std::size_t>> output = 
        {{3, {1, 2}}, {4, {5, 6}}, {10, {8, 9}}, {11, {12, 13}}};

        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        auto element = output.find(pin);
        if (element != output.end())
            _pin_value[pin] = comOr(element->second.first, element->second.second);
        else
            _pin_value[pin] = nts::Undefined;
        return _pin_value[pin];
    }
}