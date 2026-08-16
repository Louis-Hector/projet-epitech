/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4801
*/

#include "Advanced4801.hpp"
#include "Input.hpp"

namespace nts {
    Advanced4801::Advanced4801()
    {
        _pins = {{8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 18, 21, 20}, {9, 10, 11, 13, 14, 15, 16, 17}};
        _ram.resize(1024, 0);
    }

    Advanced4801::~Advanced4801()
    {
    }

    void Advanced4801::checkifinput(std::size_t i, std::pair<std::size_t, std::vector<nts::Links>> link, Tristate &statePin)
    {
        if (link.first == _pins.second[i])  { 
            for (auto &connection : link.second) { 
                auto &other = connection.getothercomponent(); 
                std::size_t otherPin = connection.getotherpin(); 
                auto input = dynamic_cast<nts::Input *>(&other); 
                if (input == nullptr) 
                    continue; 
                statePin = input->compute(otherPin); 
            }
        }
    }

    void Advanced4801::writeRAM(std::size_t address)
    {
        int valueToWrite = 0;
        for (std::size_t i = 0; i < _pins.second.size(); i++) {
            auto links = getAllLinks();
            Tristate statePin = Undefined;
            for (auto &link : links)
                checkifinput(i, link, statePin);
            if (statePin == Tristate::Undefined)
                return;
            if (statePin == Tristate::True)
                valueToWrite += pow(2, i);
        }
        _ram[address] = (std::uint8_t)valueToWrite;
    }

    Tristate Advanced4801::readRAM(std::size_t address, std::size_t pin)
    {
        uint8_t value = _ram[address];
        std::bitset<8> binaryResult(value);
        int index = -1;
        for (std::size_t i = 0; i < _pins.second.size(); i++) {
            if (_pins.second[i] == pin) {
                index = i;
                break;
            }
        }
        if (index == -1)
            return Tristate::Undefined;
        return binaryResult[index] ? Tristate::True : Tristate::False;
    }

    Tristate Advanced4801::compute(std::size_t pin)
    {
        Tristate enableState = getLink(18);
        Tristate writeState = getLink(21);
        Tristate readState = getLink(20);

        if (enableState == Tristate::True
            && (writeState == Tristate::True || readState == Tristate::True)
            && writeState != readState) {
            std::size_t address = 0;
            for (std::size_t i = 0; i < 10; i++) {
                Tristate statePin = getLink(_pins.first[i]);
                if (statePin == Tristate::Undefined)
                    return Tristate::Undefined;
                if (statePin == Tristate::True)
                    address += pow(2, i);
            }
            if (writeState == Tristate::True)
                writeRAM(address);
            if (readState == Tristate::True)
                return readRAM(address, pin);
        }
        return Tristate::Undefined;
    }
}
