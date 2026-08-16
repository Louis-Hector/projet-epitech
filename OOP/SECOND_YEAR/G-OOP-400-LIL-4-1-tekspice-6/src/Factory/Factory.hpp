/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "IComponent.hpp"
#include "AndComponent.hpp"
#include "NotComponent.hpp"
#include "OrComponent.hpp"
#include "XorComponent.hpp"
#include "Clock.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "Logger.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "Circuit.hpp"
#include "Gate4001NOR.hpp"
#include "Advanced4008.hpp"
#include "Gate4011NAND.hpp"
#include "Advanced4013.hpp"
#include "Advanced4017.hpp"
#include "Gate4030XOR.hpp"
#include "Advanced4040.hpp"
#include "Gate4069INVERTER.hpp"
#include "Gate4071OR.hpp"
#include "Gate4081AND.hpp"
#include "Advanced4094.hpp"
#include "Advanced4512.hpp"
#include "Advanced4514.hpp"
#include "Advanced2716.hpp"
#include "Advanced4801.hpp"
#include <set>
#include <functional>
#include <memory>
#include <sstream>

class Factory {
    public:
        Factory() = default;
        ~Factory() = default;
        std::unique_ptr <nts::IComponent> createComponent(const std::string &type);
        void createLink(std::string &link1, std::string &link2, Circuit &circuit);
        void isPinValid(const std::string &type, std::size_t pin);
        void isLinkValid(nts::AComponent *componentA, std::size_t pinA, nts::AComponent *componentB, std::size_t pinB);
        bool isLooping(nts::AComponent *current, nts::AComponent *searched, std::set<nts::AComponent *> &alreadyCheck);
        class FACTORY_ERROR : public std::exception
        {
            private:
                std::string _error;
            public:
                FACTORY_ERROR(std::string msg);
                const char *what() const noexcept override;
        };
    private:
};

#endif /* !FACTORY_HPP_ */
