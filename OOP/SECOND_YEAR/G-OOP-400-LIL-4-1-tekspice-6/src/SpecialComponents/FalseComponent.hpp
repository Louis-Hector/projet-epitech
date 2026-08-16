/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** FalseComponent
*/

#ifndef FALSECOMPONENT_HPP_
#define FALSECOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class FalseComponent : public AComponent{
        public:
            FalseComponent();
            ~FalseComponent();
            Tristate compute(std::size_t pin) override;
    };
}

#endif /* !FALSECOMPONENT_HPP_ */
