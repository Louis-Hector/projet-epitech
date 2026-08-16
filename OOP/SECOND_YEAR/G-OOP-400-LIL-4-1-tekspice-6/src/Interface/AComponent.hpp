/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include "Links.hpp"
#include <map>
#include <vector>

namespace nts {

    enum PinType {
        INPUT,
        OUTPUT,
        UNKNOWN,
    };
    class AComponent : public IComponent {
        protected:
            std::pair<std::vector<std::size_t>, std::vector<std::size_t>> _pins;
            std::map<std::size_t, bool> _pin_compute;
            std::map<std::size_t, nts::Tristate> _pin_value;
        private:
            std::map<std::size_t, std::vector<Links>> _links;
        public:
            AComponent(/* args */);
            virtual ~AComponent();
            PinType getPinType(std::size_t pin);
            void simulate(std::size_t tick) override;
            void setLink(std::size_t pin , IComponent &other, std::size_t otherPin) override;
            Tristate getLink(std::size_t pin);
            std::map<std::size_t, std::vector<Links>> getAllLinks();
            void restore_compute_pin();
    };
}


#endif /* !ACOMPONENT_HPP_ */