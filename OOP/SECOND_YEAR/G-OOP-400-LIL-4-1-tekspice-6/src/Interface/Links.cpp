/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** Links
*/

#include "Links.hpp"

namespace nts {

    Links::Links(IComponent &other_compo, std::size_t pino) : _other(other_compo), _otherpin(pino)
    {
    }

    IComponent &Links::getothercomponent() const
    {
        return _other;
    }

    std::size_t Links::getotherpin() const
    {
        return _otherpin;
    }
}