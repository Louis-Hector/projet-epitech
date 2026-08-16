/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "AComponent.hpp"

namespace nts {

    class Input : public AComponent {
        public:
            Input();
            ~Input();
            Tristate compute (std::size_t pin) override;
            void setState(Tristate newState);
            void simulate(std::size_t tick) override;
        private:
            Tristate _state = Tristate::Undefined;
            Tristate _nextstate = Tristate::Undefined;
            bool isNext = false;
    };
}

#endif /* !INPUT_HPP_ */
