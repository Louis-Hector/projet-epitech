/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced2716
*/

#ifndef ADVANCED2716_HPP_
#define ADVANCED2716_HPP_

#include "AComponent.hpp"
#include <bitset>
#include <cmath>
#include <fstream>
#include <memory>

namespace nts {
    class Advanced2716 : public AComponent {
        public:
            Advanced2716();
            ~Advanced2716();
            Tristate compute(std::size_t pin);
        private:
            std::vector<uint8_t> _rom;
    };
}

#endif /* !ADVANCED2716_HPP_ */
