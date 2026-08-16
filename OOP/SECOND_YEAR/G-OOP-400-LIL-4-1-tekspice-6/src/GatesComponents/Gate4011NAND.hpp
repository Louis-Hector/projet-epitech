/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Gate4011NAND
*/

#ifndef GATE4011NAND_HPP_
#define GATE4011NAND_HPP_

#include "AComponent.hpp"

namespace nts {

class Gate4011NAND : public AComponent {
    public:
        Gate4011NAND();
        ~Gate4011NAND();
        nts::Tristate comNand(std::size_t pin1, std::size_t pin2);
        nts::Tristate compute(std::size_t pin) override;
    protected:
    private:
};
}

#endif /* !GATE4011NAND_HPP_ */
