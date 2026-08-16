/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** XorComponent
*/

#ifndef XORCOMPONENT_HPP_
#define XORCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class XorComponent : public AComponent {
        public:
            XorComponent();
            ~XorComponent();
            Tristate compute(std::size_t pin) override;
    };
}

#endif /* !XORCOMPONENT_HPP_ */
