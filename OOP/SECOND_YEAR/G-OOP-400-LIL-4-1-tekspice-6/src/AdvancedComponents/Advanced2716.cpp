/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced2716
*/

#include "Advanced2716.hpp"

namespace nts {
    Advanced2716::Advanced2716()
    {
        _pins = {{8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19, 18, 20}, {9, 10, 11, 13, 14, 15, 16, 17}};

        std::ifstream file("rom.bin", std::ios::binary);
        if (!file)
            return;

        file.seekg(0, std::ios::end);
        std::size_t size = file.tellg();
        if (size != 2048)
            return;

        _rom.resize(size);
        file.seekg(0);
        for (std::size_t i = 0; i < size; i++) {
            char byte;
            file.read(&byte, 1);
            _rom[i] = static_cast<uint8_t>(byte);
        }
    }

    Advanced2716::~Advanced2716()
    {
    }

    Tristate Advanced2716::compute(std::size_t pin)
    {
        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = Tristate::Undefined;
        if (_rom.empty())
            return _pin_value[pin];
        Tristate enableState = getLink(18);
        Tristate readState = getLink(20);
        if (enableState == Tristate::False && readState == Tristate::False) {
            std::size_t address = 0;
            for (std::size_t i = 0; i < 11; i++) {
                Tristate statePin = getLink(_pins.first[i]);
                if (statePin == Tristate::Undefined)
                    return _pin_value[pin];
                if (statePin == Tristate::True)
                    address += pow(2, i);
            }
            if (address >= _rom.size())
                return _pin_value[pin];
            uint8_t value = _rom[address];
            std::bitset<8> binaryResult(value);
            int index = -1;
            for (std::size_t i = 0; i < _pins.second.size(); i++) {
                if (_pins.second[i] == pin) {
                    index = i;
                    break;
                }
            }
            if (index == -1)
                return _pin_value[pin];
            return binaryResult[index] ? _pin_value[pin] = Tristate::True : _pin_value[pin] = Tristate::False;
        }   
        return _pin_value[pin];
    }
}
