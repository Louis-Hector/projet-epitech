/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** AComponent
*/

#include "AComponent.hpp"

namespace nts {

    AComponent::AComponent(/* args */)
    {
    }

    AComponent::~AComponent()
    {
    }

    void AComponent::simulate(std::size_t tick)
    {
        (void)tick;
    }

    void AComponent::setLink(std::size_t pin , nts::IComponent &other, std::size_t otherPin)
    {
        _links[pin].push_back(Links(other, otherPin));
    }

    Tristate AComponent::getLink(std::size_t pin)
    {
        Tristate value;

        for (const auto link : _links[pin]) {
            value = link.getothercomponent().compute(link.getotherpin());
        }
        return value;
    }

    std::map<std::size_t, std::vector<Links>> AComponent::getAllLinks()
    {
        return _links;
    }

    PinType AComponent::getPinType(std::size_t pin)
    {
        for (std::size_t i = 0; i < _pins.first.size(); i++)
            if (pin == _pins.first[i])
                return PinType::INPUT;
        for (std::size_t i = 0; i < _pins.second.size(); i++)
            if (pin == _pins.second[i])
                return PinType::OUTPUT;
        return PinType::UNKNOWN;
    }

    void AComponent::restore_compute_pin() 
    {
        for (auto &[pin, status] : _pin_compute)
            status = false;
    }
}