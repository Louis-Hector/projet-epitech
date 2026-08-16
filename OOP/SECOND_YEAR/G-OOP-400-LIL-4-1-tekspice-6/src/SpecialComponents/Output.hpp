/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Output
*/

#ifndef OUTPUT_HPP_
#define OUTPUT_HPP_

#include "AComponent.hpp"

namespace nts  {
    class Output : public AComponent {
        public:
            Output();
            ~Output();
            Tristate compute (std::size_t pin) override;
    };
}

#endif /* !OUTPUT_HPP_ */
