/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** AndComponent
*/

#ifndef ANDCOMPONENT_HPP_
#define ANDCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class AndComponent : public AComponent {
        public:
            AndComponent();
            ~AndComponent();
            Tristate compute(std::size_t pin) override;
    };
}

#endif /* !ANDCOMPONENT_HPP_ */
