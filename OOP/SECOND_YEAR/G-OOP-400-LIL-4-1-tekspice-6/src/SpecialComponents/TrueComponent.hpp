/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** TrueComponent
*/

#ifndef TRUECOMPONENT_HPP_
#define TRUECOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class TrueComponent : public AComponent{
        public:
            TrueComponent();
            ~TrueComponent();
            Tristate compute(std::size_t pin) override;
    };
}

#endif /* !TRUECOMPONENT_HPP_ */
