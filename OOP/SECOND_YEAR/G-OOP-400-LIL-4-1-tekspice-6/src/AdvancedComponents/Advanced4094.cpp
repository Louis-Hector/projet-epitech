/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4094
*/

#include "Advanced4094.hpp"

namespace nts {

    Advanced4094::Advanced4094()
    {
        _pins = {{1, 2, 3, 15}, {4, 5, 6, 7, 14, 13, 12, 11, 9, 10}};
        _tab.resize(8);
        for (std::size_t i = 0; i < 8; i++)
            _tab[i] = Undefined;
    }

    Advanced4094::~Advanced4094()
    {
    }

    void Advanced4094::simulate(std::size_t tick)
    {
        Tristate clock = getLink(3);
        Tristate data = getLink(2);

        (void)tick;
        if (PClock == False && clock == True) {
            for (int i = 7; i > 0; i--) {
                _tab[i] = _tab[i - 1];
            }
            _tab[0] = data;
        }
        PClock = clock;
    }

    Tristate Advanced4094::compute(std::size_t pin)
    {
        Tristate stat_enable = getLink(15);
        Tristate strobe = getLink(1);
        std::map<std::size_t, std::size_t> outputs =
        {{4, 0}, {5, 1}, {6, 2}, {7, 3}, {14, 4}, {13, 5}, {12, 6}, {11, 7}, {9, 7}};

        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = nts::Undefined;
        if (stat_enable == False || strobe == False)
            return _pin_value[pin];
        auto element = outputs.find(pin);
        if (element != outputs.end())
            _pin_value[pin] = _tab[element->second];
        if (pin == 10) {
            if (stat_enable == True)
                _pin_value[pin] = _tab[7];
            else
                _pin_value[pin] = False;
        }
        return _pin_value[pin];
    }
}
