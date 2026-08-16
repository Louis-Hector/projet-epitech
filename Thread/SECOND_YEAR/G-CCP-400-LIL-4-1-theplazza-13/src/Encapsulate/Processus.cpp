/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Processus
*/

#include "Processus.hpp"
#include <signal.h>
#include <stdexcept>

Processus::Processus() : _pid(-1)
{
}

pid_t Processus::forkProcessus()
{
    _pid = fork();
    if (_pid == -1)
        throw std::runtime_error("fork failed");
    return _pid;
}

pid_t Processus::getpid() const
{
    return _pid;
}

int Processus::waitProcessus()
{
    int status = 0;

    if (_pid > 0) {
        waitpid(_pid, &status, 0);
        _pid = -1;
    }
    return status;
}

void Processus::quit()
{
    if (_pid > 0) {
        kill(_pid, SIGTERM);
        waitProcessus();
    }
}

bool Processus::isChild() const
{
    return _pid == 0;
}

bool Processus::isParent() const
{
    return _pid > 0;
}

int Processus::waitPid(pid_t pid)
{
    int status = 0;
    if (pid > 0)
        waitpid(pid, &status, 0);
    return status;
}