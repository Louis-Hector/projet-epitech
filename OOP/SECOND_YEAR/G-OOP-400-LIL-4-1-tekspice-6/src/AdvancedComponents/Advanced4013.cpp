/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4013
*/

#include "Advanced4013.hpp"

namespace nts {

    Advanced4013::Advanced4013()
    {
        _pins = {{3, 5, 6, 4, 9, 8, 10, 11}, {1, 2, 13, 12}};
        _output.resize(4);
        for (std::size_t i = 0; i < 4; i++)
            _output[i] = Undefined;
    }

    Advanced4013::~Advanced4013()
    {
    }

    Tristate Advanced4013::inversestate(Tristate &data)
    {
        if (data == Tristate::True)
            return Tristate::False;
        else if (data == Tristate::False)
            return Tristate::True;
        else
            return Tristate::Undefined;
    }

    void Advanced4013::verifsetreset(std::size_t pin1, std::size_t pin2, int pos, int pos2)
    {
        Tristate reset = getLink(pin1);
        Tristate set = getLink(pin2);

        if (set == Tristate::True && reset == Tristate::True) {
            _output[pos] = Tristate::True;
            _output[pos2] = Tristate::True;
            return;
        }
        if (set == Tristate::True) {
            _output[pos] = Tristate::True;
            _output[pos2] = Tristate::False;
            return;
        }
        if (reset == Tristate::True) {
            _output[pos] = Tristate::False;
            _output[pos2] = Tristate::True;
            return;
        }
        return;
    }

    void Advanced4013::simulate(std::size_t tick)
    {
        Tristate clock = getLink(3);
        Tristate clock1 = getLink(11);
        Tristate data1 = getLink(9);
        Tristate data = getLink(5);

        (void)tick;
        if (PClock == False && clock == True) {
            _output[0] = data;
            _output[1] = inversestate(data);
        }
        if (PClock1 == False && clock1 == True) {
            _output[2] = data1;
            _output[3] = inversestate(data1);
        }
        PClock = clock;
        PClock1 = clock1;
    }

    
    Tristate Advanced4013::compute(std::size_t pin)
    {
        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        verifsetreset(4, 6, 0, 1);
        verifsetreset(10, 8, 2, 3);
        _pin_value[pin] = nts::Undefined;
        if (pin == 1)
            _pin_value[pin] = _output[0];
        if (pin == 2)
            _pin_value[pin] = _output[1];
        if (pin == 13)
            _pin_value[pin] = _output[2];
        if (pin == 12)
            _pin_value[pin] = _output[3];
        return _pin_value[pin];
    }
}
