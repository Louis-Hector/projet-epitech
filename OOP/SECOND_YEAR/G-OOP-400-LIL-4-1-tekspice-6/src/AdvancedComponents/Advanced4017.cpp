/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4017
*/

#include "Advanced4017.hpp"

namespace nts {

    Advanced4017::Advanced4017()
    {
        _pins = {{14, 13, 15}, {3, 2, 4, 7, 10, 1, 5, 6, 9, 11, 12}};
    }

    Advanced4017::~Advanced4017()
    {
    }

    void Advanced4017::simulate(std::size_t tick)
    {
        Tristate clock = getLink(14);
        Tristate clock1 = getLink(13);
        Tristate stat_reset = getLink(15);

        (void)tick;
        if (stat_reset == True) {
            counter = 0;
            PClock = clock;
            PClock1 = clock1;
            return;
        }
        if (PClock == False && clock == True && clock1 == False)
            counter = (counter + 1) % 10;
        if (PClock1 == True && clock1 == False && clock == True) 
            counter = (counter + 1) % 10;
        PClock = clock;
        PClock1 = clock1;
    }

    Tristate Advanced4017::compute(std::size_t pin) 
    {
        Tristate clock = getLink(14);
        Tristate clock1 = getLink(13);
        std::map<std::size_t, std::size_t> output 
        {{3, 0}, {2, 1}, {4, 2}, {7, 3}, {10, 4}, {1, 5}, {5, 6}, {6, 7}, {9, 8}, {11, 9}};

        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = nts::Undefined;
        if (clock == Undefined || clock1 == Undefined)
            return _pin_value[pin];
        auto element = output.find(pin);
        if (element != output.end()) {
            if (counter == element->second)
                _pin_value[pin] = nts::True;
            else
                _pin_value[pin] = nts::False;
        }
        if (pin == 12) {
            if (counter >= 5)
                _pin_value[pin] = nts::False;
            else
                _pin_value[pin] = nts::True;
        }
        return _pin_value[pin];
    }   
}