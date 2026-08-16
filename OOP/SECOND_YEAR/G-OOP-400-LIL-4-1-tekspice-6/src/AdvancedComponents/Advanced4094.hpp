/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4094
*/

#ifndef ADVANCED4094_HPP_
#define ADVANCED4094_HPP_

#include "AComponent.hpp"

namespace nts {

    class Advanced4094 : public AComponent {
        public:
            Advanced4094();
            ~Advanced4094();
            void simulate(std::size_t tick);
            Tristate compute(std::size_t pin);
        protected:
        private:
            Tristate PClock = Undefined;
            std::vector<Tristate> _tab;
    };
}

#endif /* !ADVANCED4094_HPP_ */
