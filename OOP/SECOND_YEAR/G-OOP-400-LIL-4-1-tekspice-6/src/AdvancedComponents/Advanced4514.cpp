/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4514
*/

#include "Advanced4514.hpp"

namespace nts {

    Advanced4514::Advanced4514()
    { 
        _pins = {{1, 2, 3, 21, 22, 23}, {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15}};
        last.resize(4, Undefined);
    }

    Advanced4514::~Advanced4514()
    {
    }

    nts::Tristate Advanced4514::compute(std::size_t pin)
    {
        nts::Tristate inhibit = getLink(23);
        nts::Tristate strobe = getLink(1);
        std::size_t decimal = {};
        bool valid_out = false;

        for (std::size_t i = 0; i < _pins.second.size(); i++)
            if (_pins.second[i] == pin)
                valid_out = true;
        if (valid_out == false)
            return nts::Undefined;
        if (inhibit == nts::True)
            return nts::False;
        if (inhibit == nts::Undefined)
            return nts::Undefined;
        if (strobe == nts::True) {
            std::vector<nts::Tristate> _allinput = {getLink(2), getLink(3), getLink(21), getLink(22)};
            for (std::size_t i = 0; i < _allinput.size(); i++) {
                if (_allinput[i] == nts::Undefined)
                    return nts::Undefined;
                if (_allinput[i] == nts::True)
                    decimal+= pow(2, i);
            }
            last = _allinput;
        } else {
            for (std::size_t i = 0; i < last.size(); i++) {
                if (last[i] == nts::Undefined)
                    return nts::Undefined;
                if (last[i] == nts::True)
                    decimal+= pow(2, i);
            }
        }
        if (_pins.second[decimal] == pin) 
            return nts::True;
        return nts::False;
    }
}