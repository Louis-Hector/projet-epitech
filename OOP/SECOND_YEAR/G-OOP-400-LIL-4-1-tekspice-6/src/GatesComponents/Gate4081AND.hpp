/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Gate4081AND
*/

#ifndef GATE4081AND_HPP_
#define GATE4081AND_HPP_

#include "AComponent.hpp"
#include "AndComponent.hpp"

namespace nts {

    class Gate4081AND : public AComponent {
        public:
            Gate4081AND();
            ~Gate4081AND();
            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate comAnd(std::size_t pin1, std::size_t pin2);
        private:
    };
}

#endif /* !GATE4081AND_HPP_ */
