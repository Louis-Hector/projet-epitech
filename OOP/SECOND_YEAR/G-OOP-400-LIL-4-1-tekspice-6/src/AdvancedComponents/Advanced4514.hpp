/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4514
*/

#ifndef ADVANCED4514_HPP_
#define ADVANCED4514_HPP_

#include "AComponent.hpp"
#include <cmath>

namespace nts {

    class Advanced4514 : public AComponent {
        public:
            Advanced4514();
            ~Advanced4514();
            nts::Tristate compute(std::size_t pin);
        private:
            std::vector<Tristate> last = {};
    };

}

#endif /* !ADVANCED4514_HPP_ */
