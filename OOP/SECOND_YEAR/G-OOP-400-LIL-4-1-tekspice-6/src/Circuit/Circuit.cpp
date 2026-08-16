/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** Circuit
*/

#include "Circuit.hpp"

void Circuit::addComponent(std::string &name, std::unique_ptr<nts::IComponent> &component, std::string type)
{
    _circuit.insert(std::make_pair(name, std::make_pair(std::move(component), type)));
}

void Circuit::addLinks(std::string &link1, std::string &links2)
{
    _links.insert(std::make_pair(link1, links2));
}

bool Circuit::searchComponent(const std::string &name)
{
    for (auto i = _circuit.begin(); i != _circuit.end(); i++) {
        if (i->first == name)
            return true;
    }
    return false;
}

void Circuit::setLoop(void)
{
    _isloop = true;
}

std::map<std::string, std::pair<std::unique_ptr<nts::IComponent>, std::string>>& Circuit::getCircuit()
{
    return _circuit;
}

void Circuit::simulate_tick()
{
    _ticks++;
    for (auto it = _circuit.begin(); it != _circuit.end(); it++) {
        auto *component = dynamic_cast<nts::AComponent *>(it->second.first.get());
        if (component == NULL)
            continue;
        it->second.first->simulate(_ticks);
        component->restore_compute_pin();
    }
}

static void verif_state(nts::Tristate state, std::string name)
{
    if (state == nts::False)
        std::cout << "  " << name << ": 0" << std::endl;
    else if (state == nts::True)
        std::cout << "  " << name << ": 1" << std::endl;
    else
        std::cout << "  " << name << ": U" << std::endl;
}

void Circuit::displayStates()
{
    std::cout << "tick: " << _ticks << std::endl;
    std::cout << "input(s):" << std::endl;
    for (auto it = _circuit.begin(); it != _circuit.end(); it++) {
        auto input = dynamic_cast<nts::Input *>(it->second.first.get());
        if (input != nullptr)
            verif_state(input->compute(1), it->first);
        auto clock = dynamic_cast<nts::Clock *>(it->second.first.get());
        if (clock != nullptr)
            verif_state(clock->compute(1), it->first);
    }
    std::cout << "output(s):" << std::endl;
    for (auto it = _circuit.begin(); it != _circuit.end(); it++) {
        auto output = dynamic_cast<nts::Output *>(it->second.first.get());
        if (output != nullptr) {
            verif_state(output->compute(1), it->first);
        }
    }
}

std::size_t Circuit::getTicks()
{
    return _ticks;
}