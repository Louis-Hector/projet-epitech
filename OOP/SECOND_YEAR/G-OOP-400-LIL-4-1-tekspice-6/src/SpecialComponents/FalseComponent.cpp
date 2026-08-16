/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** FalseComponent
*/

#include "FalseComponent.hpp"

namespace nts {
    FalseComponent::FalseComponent()
    {
        _pins = {{},{1}};
    }

    FalseComponent::~FalseComponent()
    {
    }

    Tristate FalseComponent::compute(std::size_t pin) 
    {
        (void)pin;
        return False;
    }
}