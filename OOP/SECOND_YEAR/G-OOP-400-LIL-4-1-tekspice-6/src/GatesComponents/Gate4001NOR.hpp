/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Gate4001NOR
*/

#ifndef GATE4001NOR_HPP_
#define GATE4001NOR_HPP_

#include "AComponent.hpp"

namespace nts {

    class Gate4001NOR : public AComponent {
        public:
            Gate4001NOR();
            ~Gate4001NOR();
            nts::Tristate comNor(std::size_t pin1, std::size_t pin2);
            nts::Tristate compute(std::size_t pin) override;
        protected:
        private:
    };
}

#endif /* !GATE4001NOR_HPP_ */
