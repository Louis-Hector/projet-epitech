/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"

namespace nts {
    TrueComponent::TrueComponent()
    {
        _pins = {{},{1}};
    }

    TrueComponent::~TrueComponent()
    {
    }

    Tristate TrueComponent::compute(std::size_t pin) 
    {
        (void)pin;
        return True;
    }
}
