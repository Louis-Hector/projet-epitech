/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Gate4071OR
*/

#ifndef GATE4071OR_HPP_
#define GATE4071OR_HPP_

#include "AComponent.hpp"

namespace nts {

    class Gate4071OR : public AComponent{
        public:
            Gate4071OR();
            ~Gate4071OR();
            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate comOr(std::size_t pin1, std::size_t pin2);
        protected:
        private:
    };
}

#endif /* !GATE4071OR_HPP_ */
