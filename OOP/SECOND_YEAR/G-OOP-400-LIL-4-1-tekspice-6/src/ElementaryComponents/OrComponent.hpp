/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** OrComponent
*/

#ifndef ORCOMPONENT_HPP_
#define ORCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class OrComponent : public AComponent {
        public:
            OrComponent();
            ~OrComponent();
            Tristate compute(std::size_t pin) override;
    };
}

#endif /* !ORCOMPONENT_HPP_ */
