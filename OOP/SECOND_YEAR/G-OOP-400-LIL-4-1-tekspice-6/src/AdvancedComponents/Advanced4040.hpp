/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Advanced4040
*/

#ifndef ADVANCED4040_HPP_
#define ADVANCED4040_HPP_

#include "AComponent.hpp"

namespace nts {

    class Advanced4040 : public AComponent {
        public:
            Advanced4040();
            ~Advanced4040();
            void simulate(std::size_t tick);
            nts::Tristate compute(std::size_t pin);
        private:
            std::string _tick_to_binary = "";
            int counter {};
            nts::Tristate PClock;
    };

}

#endif /* !ADVANCED4040_HPP_ */
