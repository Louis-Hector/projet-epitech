/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4013
*/

#ifndef ADVANCED4013_HPP_
#define ADVANCED4013_HPP_

#include "AComponent.hpp"

namespace nts {

    class Advanced4013 : public AComponent{
        public:
            Advanced4013();
            ~Advanced4013();
            void simulate(std::size_t tick);
            void checkstate(Tristate &set, Tristate &reset, Tristate &out, Tristate &iout);
            void verifsetreset(std::size_t pin1, std::size_t pin2, int pos, int pos2);
            Tristate inversestate(Tristate &data);
            Tristate compute(std::size_t pin);
        protected:
        private:
            Tristate PClock = Undefined;
            Tristate PClock1 = Undefined;
            std::vector<Tristate> _output;
    };
}

#endif /* !ADVANCED4013_HPP_ */
