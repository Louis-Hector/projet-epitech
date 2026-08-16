/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4008
*/

#include "Advanced4008.hpp"

namespace nts {
    Advanced4008::Advanced4008()
    {
        _pins = {{1, 2, 3, 4, 5, 6, 7, 9, 15}, {10, 11, 12, 13, 14}};
    }

    Advanced4008::~Advanced4008()
    {
    }

    std::pair<Tristate, Tristate> Advanced4008::computeAdd(std::size_t pin1, std::size_t pin2, nts::Tristate cin)
    {
        auto s1 = getLink(pin1);
        auto s2 = getLink(pin2);

        if (cin == Undefined || s1 == Undefined || s2 == Undefined)
            return {Undefined, Undefined};
        int value = ((s1 ^ s2) ^ cin);
        int value_cin = (s1 & s2) | (cin & (s1 ^ s2));
        Tristate new_cin = Undefined;
        if (value_cin == 1)
            new_cin = nts::True;
        else if (value_cin == 0)
            new_cin = nts::False;
        else
            new_cin = nts::Undefined;
        if (value == 1)
            return std::make_pair(new_cin, nts::True);
        else if (value == 0)
            return std::make_pair(new_cin, nts::False);
        else
            return std::make_pair(new_cin, nts::Undefined);
    }

    nts::Tristate Advanced4008::compute(std::size_t pin)
    {
        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        nts::Tristate cin = getLink(9);
        std::pair sumab1 = computeAdd(6, 7, cin);
        std::pair sumab2 = computeAdd(4, 5, sumab1.first);
        std::pair sumab3 = computeAdd(2, 3, sumab2.first);
        std::pair sumab4 = computeAdd(1, 15, sumab3.first);
        _pin_value[pin] = nts::Undefined;
        if (pin == 10)
            _pin_value[pin] = sumab1.second;
        if (pin == 11)
            _pin_value[pin] = sumab2.second;
        if (pin == 12)
            _pin_value[pin] = sumab3.second;
        if (pin == 13)
            _pin_value[pin] = sumab4.second;
        if (pin == 14)
            _pin_value[pin] = sumab4.first;
        return _pin_value[pin];
    }
}