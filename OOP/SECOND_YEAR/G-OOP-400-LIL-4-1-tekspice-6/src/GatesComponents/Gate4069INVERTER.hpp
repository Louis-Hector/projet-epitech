/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Gate4069INVERTER
*/

#ifndef GATE4069INVERTER_HPP_
#define GATE4069INVERTER_HPP_

#include "AComponent.hpp"

namespace nts {

    class Gate4069INVERTER : public AComponent {
        public:
            Gate4069INVERTER();
            ~Gate4069INVERTER();
            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate comInverter(std::size_t pin);
        protected:
        private:
    };
}
#endif /* !GATE4069INVERTER_HPP_ */
