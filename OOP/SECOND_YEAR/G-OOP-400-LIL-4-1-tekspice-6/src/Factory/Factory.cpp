/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Factory
*/

#include "Factory.hpp"

std::unique_ptr <nts::IComponent> Factory::createComponent(const std::string &type)
{
    static const std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> creators = {
        { "and", [] { return std::make_unique<nts::AndComponent>(); }},
        { "not", [] { return std::make_unique<nts::NotComponent>();}},
        { "or", [] { return std::make_unique<nts::OrComponent>();}},
        { "xor", [] { return std::make_unique<nts::XorComponent>();}},
        { "clock", [] { return std::make_unique<nts::Clock>();}},
        { "true", [] { return std::make_unique<nts::TrueComponent>(); }},
        { "false", [] { return std::make_unique<nts::FalseComponent>(); }},
        { "logger", [] { return std::make_unique<nts::Logger>();}},
        { "input", [] { return std::make_unique<nts::Input>(); }},
        { "output", [] { return std::make_unique<nts::Output>();}},
        { "2716", [] { return std::make_unique<nts::Advanced2716>();}},
        { "4001", [] { return std::make_unique<nts::Gate4001NOR>();}},
        { "4008", [] { return std::make_unique<nts::Advanced4008>();}},
        { "4011", [] { return std::make_unique<nts::Gate4011NAND>();}},
        { "4013", [] { return std::make_unique<nts::Advanced4013>();}},
        { "4017", [] { return std::make_unique<nts::Advanced4017>();}},
        { "4030", [] { return std::make_unique<nts::Gate4030XOR>();}},
        { "4040", [] { return std::make_unique<nts::Advanced4040>();}},
        { "4069", [] { return std::make_unique<nts::Gate4069INVERTER>();}},
        { "4071", [] { return std::make_unique<nts::Gate4071OR>();}},
        { "4081", [] { return std::make_unique<nts::Gate4081AND>();}},
        { "4094", [] { return std::make_unique<nts::Advanced4094>();}},
        { "4512", [] { return std::make_unique<nts::Advanced4512>();}},
        { "4514", [] { return std::make_unique<nts::Advanced4514>();}},
        { "4801", [] { return std::make_unique<nts::Advanced4801>();}}
    };
    auto component = creators.find(type);
    if (component == creators.end())
        throw std::runtime_error("Unknown component type: " + type);
    return component->second();
}

void Factory::isLinkValid(nts::AComponent *componentA, std::size_t pinA, nts::AComponent *componentB, std::size_t pinB)
{
    nts::PinType typeA = componentA->getPinType(pinA);
    nts::PinType typeB = componentB->getPinType(pinB);
    if (typeA == typeB && typeA == nts::PinType::INPUT)
        throw FACTORY_ERROR("You can't link a input pin to another one");
    if (typeA == typeB && typeA == nts::PinType::OUTPUT)
        throw FACTORY_ERROR("You can't link a output pin to another one");
    if (typeA == nts::PinType::UNKNOWN || typeB == nts::PinType::UNKNOWN)
        throw FACTORY_ERROR("You try to link a pin to an unknown one");
}

void Factory::isPinValid(const std::string &type, std::size_t pin)
{
    const std::map<std::string, std::pair<std::size_t, std::size_t>> typePin =
    {
        {"input", {1, 1}}, {"output", {1, 1}}, {"true", {1, 1}}, {"false", {1, 1}}, {"clock", {1, 1}}, {"logger", {1, 10}},
        {"not", {1, 2}}, {"and", {1, 3}}, {"or", {1, 3}}, {"xor", {1, 3}},
        {"4001", {1, 13}}, {"4011", {1, 13}}, {"4030", {1, 13}}, {"4069", {1, 13}}, {"4071", {1, 13}}, {"4081", {1, 13}},
        {"2716", {1, 23}}, {"4008", {1, 16}}, {"4013", {1, 13}}, {"4017", {1, 15}}, {"4040", {1, 16}}, {"4094", {1, 15}}, {"4512", {1, 15}}, {"4514", {1, 23}}, {"4801", {1, 23}}
    };

    auto current = typePin.find(type);
    if (current == typePin.end())
        throw FACTORY_ERROR("Type " + type + " not found");
    auto [min, max] = current->second;
    if (pin < min || pin > max)
        throw FACTORY_ERROR("Invalid pin '" + std::to_string(pin) + "' for " + type);
}

bool Factory::isLooping(nts::AComponent *current, nts::AComponent *searched, std::set<nts::AComponent *> &alreadyVisited)
{
    if (current == searched)
        return true;
    alreadyVisited.insert(current);
    for (auto &[pin, links] : current->getAllLinks()) {
        for (auto &link : links) {
            auto otherComponent = dynamic_cast<nts::AComponent *>(&link.getothercomponent());
            if (!otherComponent)
                continue;
            if (alreadyVisited.find(otherComponent) != alreadyVisited.end())
                continue;
            if (isLooping(otherComponent, searched, alreadyVisited))
                return true;
        }
    }
    return false;
}

void Factory::createLink(std::string &link1, std::string &link2, Circuit &circuit)
{
    std::string nameA = link1.substr(0, link1.find(':'));
    std::string nameB = link2.substr(0, link2.find(':'));

    std::string typeCompA = circuit.getCircuit()[nameA].second;
    std::string typeCompB = circuit.getCircuit()[nameB].second;

    std::stringstream pinStrA(link1.substr(link1.find(':') + 1));
    std::size_t pinA {};
    pinStrA >> pinA;
    std::stringstream pinStrB(link2.substr(link2.find(':') + 1));
    std::size_t pinB {};
    pinStrB >> pinB;

    auto componentA = dynamic_cast<nts::AComponent *>(circuit.getCircuit()[nameA].first.get());
    if (!componentA)
        return;
    auto componentB = dynamic_cast<nts::AComponent *>(circuit.getCircuit()[nameB].first.get());
    if (!componentB)
        return;

    isPinValid(typeCompA, pinA);
    isPinValid(typeCompB, pinB);

    if (typeCompA != "4801" && typeCompB != "4801")
        isLinkValid(componentA, pinA, componentB, pinB);

    std::set<nts::AComponent *> alreadyVisited;
    if (isLooping(componentA, componentB, alreadyVisited))
        circuit.setLoop();
    //throw FACTORY_ERROR("You create a loop by linking " + nameA + ":" + std::to_string(pinA) + " to " + nameB + ":" + std::to_string(pinB));
    componentA->setLink(pinA, *componentB, pinB);
    componentB->setLink(pinB, *componentA, pinA);
}

Factory::FACTORY_ERROR::FACTORY_ERROR(std::string msg) : _error(msg) {

}

const char *Factory::FACTORY_ERROR::what() const noexcept {
    return _error.c_str();
}
