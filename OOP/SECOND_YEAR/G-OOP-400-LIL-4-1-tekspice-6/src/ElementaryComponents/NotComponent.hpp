/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** NotComponent
*/

#ifndef NOTCOMPONENT_HPP_
#define NOTCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class NotComponent : public AComponent {
        public:
            NotComponent();
            ~NotComponent();
            Tristate compute(std::size_t pin) override;
    };
}

#endif /* !NOTCOMPONENT_HPP_ */
