/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4040
*/

#include "Advanced4040.hpp"

namespace nts {

    Advanced4040::Advanced4040()
    {
        _pins = {{10, 11}, {1, 2, 3, 4, 5, 6, 7, 9, 12, 13, 14, 15}};
        _tick_to_binary.resize(12);
        for (std::size_t i = 0; i < 12; i++)
            _tick_to_binary[i] = 'U';
    }

    Advanced4040::~Advanced4040()
    {
    }

    void Advanced4040::simulate(std::size_t tick)
    {
        (void)tick;
        nts::Tristate clock = getLink(10);

        if (PClock == True && clock == False)
            counter = (1 + counter) % 4096;
        PClock = clock;
        int tmp = counter;
        for (int i = 11; i >= 0; i--) {
            if (tmp % 2 == 1)
                _tick_to_binary[i] = '1';
            else
                _tick_to_binary[i] = '0';
            tmp /= 2;
        }
    }

    nts::Tristate Advanced4040::compute(std::size_t pin) 
    {
        nts::Tristate reset = getLink(11);
        std::map<std::size_t, std::size_t> outputs =
        {{9, 0}, {7, 1}, {6, 2}, {5, 3}, {3, 4}, {2, 5}, {4, 6}, {13, 7}, {12, 8}, {14, 9}, {15, 10}, {1, 11}};

        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = nts::Undefined;
        if (reset == nts::True) {
            counter = 0;
            for (std::size_t i = 0; i < 12; i++)
                _tick_to_binary[i] = '0';
            _pin_value[pin] = nts::False;
            return _pin_value[pin];
        }
        auto element = outputs.find(pin);
        if (element != outputs.end()) {
            std::size_t pos = 11 - element->second;
            if (_tick_to_binary[pos] == '1')
                _pin_value[pin] = nts::True;
            else if (_tick_to_binary[pos] == '0')
                _pin_value[pin] = nts::False;
            else
                _pin_value[pin] = nts::Undefined;
        }
        return _pin_value[pin];
    }
}
