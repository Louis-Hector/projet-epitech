/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4801
*/

#ifndef ADVANCED4801_HPP_
#define ADVANCED4801_HPP_

#include "AComponent.hpp"
#include <cstdint>
#include <bitset>
#include <cmath>

namespace nts {
    class Advanced4801 : public AComponent {
        public:
            Advanced4801();
            ~Advanced4801();
            Tristate compute(std::size_t pin);
            void writeRAM(std::size_t address);
            Tristate readRAM(std::size_t address, std::size_t pin);
            void checkifinput(std::size_t i, std::pair<std::size_t, std::vector<nts::Links>> link, Tristate &statePin);
        private:
            std::vector<uint8_t> _ram;
    };
}

#endif /* !ADVANCED4801_HPP_ */
