/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Gate4030XOR
*/

#ifndef GATE4030XOR_HPP_
#define GATE4030XOR_HPP_

#include "AComponent.hpp"

namespace nts {
    class Gate4030XOR : public AComponent{
        public:
            Gate4030XOR();
            ~Gate4030XOR();
            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate comXor(std::size_t pin1, std::size_t pin2);
        protected:
        private:
    };
}

#endif /* !GATE4030XOR_HPP_ */
