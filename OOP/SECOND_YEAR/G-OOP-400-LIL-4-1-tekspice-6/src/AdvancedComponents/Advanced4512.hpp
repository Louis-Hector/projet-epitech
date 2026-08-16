/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4512
*/

#ifndef ADVANCED4512_HPP_
#define ADVANCED4512_HPP_

#include "AComponent.hpp"
#include <cmath>

namespace nts {

    class Advanced4512 : public AComponent {
        public:
            Advanced4512();
            ~Advanced4512();
            Tristate compute(std::size_t pin);
        protected:
        private:
    };
}

#endif /* !ADVANCED4512_HPP_ */
