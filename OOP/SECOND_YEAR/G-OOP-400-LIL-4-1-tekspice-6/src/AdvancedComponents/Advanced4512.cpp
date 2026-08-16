/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4512
*/

#include "Advanced4512.hpp"

namespace nts {

    Advanced4512::Advanced4512()
    {
        _pins = {{1, 2, 3, 4, 5, 6, 7, 9,10, 15, 11, 12, 13}, {14}};
    }

    Advanced4512::~Advanced4512()
    {
    }

    Tristate Advanced4512::compute(std::size_t pin)
    {
        Tristate stat_inhibit = getLink(10);
        Tristate stat_enable = getLink(15);
        std::vector<Tristate> adress = {getLink(11), getLink(12), getLink(13)};
        std::size_t decimal = {};

        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = Undefined;
        if (stat_enable == True)
            return _pin_value[pin];
        if (stat_inhibit == True) {
            _pin_value[pin] = nts::False;
            return _pin_value[pin];
        }
        for (std::size_t i = 0; i < adress.size(); i++) {
            if (adress[i] == Undefined) {
                _pin_value[pin] = Undefined;
                return _pin_value[pin];
            }
            if (adress[i] == True)
                decimal += pow(2, i);
        }
        if (pin == 14) {
            Tristate input = getLink(_pins.first[decimal]);
            if (input == True)
                _pin_value[pin] = True;
            else if (input == False)
                _pin_value[pin] = False;
            else
                _pin_value[pin] = Undefined;
        }
        return _pin_value[pin];
    }
}
