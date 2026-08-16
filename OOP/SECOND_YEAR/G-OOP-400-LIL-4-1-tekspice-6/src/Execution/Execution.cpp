/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Execution
*/

#include "Execution.hpp"

Execution::Execution()
{
}

Execution::~Execution()
{
}

void Execution::execExit() const
{
    exit(0);
}

void Execution::execDisplay(Circuit &circuit) const
{
    circuit.displayStates();
}

void Execution::execInput(std::string line, Circuit &circuit)
{
    std::string component = line.substr(0, line.find('='));
    std::string value = line.substr(line.find('=') + 1);
    nts::Tristate newState;

    if (circuit.searchComponent(component) == false) {
        std::cout << "Name '" << component << "' unknown" << std::endl;
        return;
    }
    if (value != "0" && value != "1" && value != "U") {
        std::cout << "State '" << value << "' unknown" << std::endl;
        return;
    }
    if (value == "0")
        newState = nts::False;
    else if (value == "1")
        newState = nts::True;
    else
        newState = nts::Undefined;
    auto compo_input = dynamic_cast<nts::Input *>(circuit.getCircuit()[component].first.get());
    if (compo_input != nullptr) {
        compo_input->setState(newState);
        return;
    }
    auto compo_clock = dynamic_cast<nts::Clock *>(circuit.getCircuit()[component].first.get());
    if (compo_clock != nullptr) {
        compo_clock->setState(newState);
        return;
    }
    std::cout << "The component isn't a input or clock" << std::endl;
}

void Execution::execSimulate(Circuit &circuit)
{
    circuit.simulate_tick();
}

volatile std::sig_atomic_t statussignal;

void signalHandler(int sig) 
{
    if (sig == SIGINT)
        statussignal = 1;
}

void Execution::execLoop(Circuit &circuit)
{
    std::signal(SIGINT, signalHandler);
    while (!statussignal) {
        execSimulate(circuit);
        execDisplay(circuit);
    }
}

void Execution::execSimDis(Circuit &circuit)
{
    circuit.simulate_tick();
    circuit.displayStates();
}

void Execution::execCircuit(Circuit &circuit)
{
    std::cout << "Component(s):" << std::endl;
    for (auto it = circuit.getCircuit().begin(); it != circuit.getCircuit().end(); it++) {
        std::cout << "Name: " << it->first << " Type: " << it->second.second << std::endl;
        auto component = dynamic_cast<nts::AComponent *>(it->second.first.get());
        if (component == nullptr)
            continue;
        auto links = component->getAllLinks();
        std::cout << "Link(s):" << std::endl;
        for (auto i = links.begin(); i != links.end(); i++) {
            std::cout << i->first << "<---->";
            for (auto j = i->second.begin(); j != i->second.end(); j++) {
                std::cout << j->getotherpin() << std::endl;
            }
        }
    }
}

void Execution::execCommand(std::string line, Circuit &circuit)
{
    int pos = line.find('=');

    if (pos != -1)
        execInput(line, circuit);
    if (line == "display")
        execDisplay(circuit);
    if (line == "simulate")
        execSimulate(circuit);
    if (line == "loop") {
        execLoop(circuit);
        statussignal = 0;
    }
    if (line == "sd")
        execSimDis(circuit);
    if (line == "circuit")
        execCircuit(circuit);
    if (line == "exit")
        execExit();
}

static std::string remove_spaces(const std::string line)
{
    std::string string_clean = "";

    for (std::size_t i = 0; i < line.size(); i++)
        if (line[i] != ' ')
            string_clean += line[i];
    return string_clean;
}

void Execution::launchShell(Circuit &circuit)
{
    std::string line;

    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        std::string word;
        int nb_args {};
        std::string clean_str = remove_spaces(line);
        std::stringstream ss(clean_str);
        while (ss >> word)
            nb_args++;
        if (nb_args > 1) {
            std::cout << "> ";
            continue;
        }
        execCommand(clean_str, circuit);
        std::cout << "> ";
    }
}