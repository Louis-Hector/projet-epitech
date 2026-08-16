/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** Links
*/

#ifndef LINKS_HPP_
#define LINKS_HPP_

#include "IComponent.hpp"

namespace nts {
    class Links
    {
    private:
        IComponent &_other;
        std::size_t _otherpin;
    public:
        Links(IComponent &other_compo, std::size_t pino);
        IComponent &getothercomponent() const;
        std::size_t getotherpin() const;
    };
}

#endif /* !LINKS_HPP_ */