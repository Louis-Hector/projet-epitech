/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "IComponent.hpp"
#include "Clock.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "AComponent.hpp"
#include <memory>
#include <iostream>

class Circuit
{
private:
    std::map<std::string, std::pair<std::unique_ptr<nts::IComponent>, std::string>> _circuit;
    std::map<std::string, std::string> _links;
    std::size_t _ticks {};
    bool _isloop = false;
public:
    Circuit() = default;
    ~Circuit() = default;
    void addComponent(std::string &name, std::unique_ptr<nts::IComponent> &component, std::string type);
    void addLinks(std::string &link1, std::string &links2);
    bool searchComponent(const std::string &name);
    std::map<std::string, std::pair<std::unique_ptr<nts::IComponent>, std::string>>& getCircuit();
    std::size_t getTicks();
    void simulate_tick(); 
    void displayStates();
    void setLoop();
};

#endif /* !CIRCUIT_HPP_ */
