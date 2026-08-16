/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4017
*/

#ifndef ADVANCED4017_HPP_
#define ADVANCED4017_HPP_

#include "AComponent.hpp"
#include "Input.hpp"

namespace nts {

    class Advanced4017 : public AComponent {
        public:
            Advanced4017();
            ~Advanced4017();
            void simulate(std::size_t tick);
            Tristate compute(std::size_t pin);
        protected:
        private:
            std::size_t counter {};
            Tristate PClock = Undefined;
            Tristate PClock1 =  Undefined;
    };
}

#endif /* !ADVANCED4017_HPP_ */
