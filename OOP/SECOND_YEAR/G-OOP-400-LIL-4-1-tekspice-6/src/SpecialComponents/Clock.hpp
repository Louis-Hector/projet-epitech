/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include "AComponent.hpp"

namespace nts {
    class Clock : public AComponent{
        public:
            Clock();
            ~Clock();
            nts::Tristate compute (std::size_t pin) override;
            void setState(Tristate newState);
            void simulate(std::size_t tick) override;
        private:
            Tristate _state = Tristate::Undefined;
            Tristate _nextstate = Tristate::Undefined;
            bool isNext = false;
    };
}

#endif /* !CLOCK_HPP_ */
