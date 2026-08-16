/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4008
*/

#ifndef ADVANCED4008_HPP_
#define ADVANCED4008_HPP_

#include "AComponent.hpp"

namespace nts {

    class Advanced4008 : public AComponent{
        public:
            Advanced4008();
            ~Advanced4008();
            std::pair<Tristate, Tristate> computeAdd(std::size_t pin1, std::size_t pin2, nts::Tristate cin);
            nts::Tristate compute(std::size_t pin);
        protected:
        private:
    };
}

#endif /* !ADVANCED4008_HPP_ */
