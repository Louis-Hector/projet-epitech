/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Execution
*/

#ifndef EXECUTION_HPP_
#define EXECUTION_HPP_

#include "Circuit.hpp"
#include "Input.hpp"
#include "IComponent.hpp"
#include "AComponent.hpp"
#include <csignal>
#include <sstream>
#include <iostream>

class Execution {
    public:
        Execution();
        ~Execution();
        void execExit() const;
        void execDisplay(Circuit &circuit) const;
        void execInput(std::string line, Circuit &circui);
        void execSimulate(Circuit &circuit);
        void execLoop(Circuit &circuit);
        void execCommand(std::string line, Circuit &circuit);
        void execCircuit(Circuit &circuit);
        void execSimDis(Circuit &circuit);
        void launchShell(Circuit &circuit);
    protected:
    private:
};

#endif /* !EXECUTION_HPP_ */