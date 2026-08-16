/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "AComponent.hpp"
#include <cmath>
#include <fstream>

namespace nts {
    class Logger : public AComponent {
        public:
            Logger();
            ~Logger();
            void simulate(std::size_t tick);
            Tristate compute(std::size_t pin);
        private:
            Tristate _prevClock = Tristate::Undefined;
    };
}

#endif /* !LOGGER_HPP_ */
