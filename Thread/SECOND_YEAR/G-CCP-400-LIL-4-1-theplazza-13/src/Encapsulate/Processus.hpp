/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Processus
*/

#ifndef PROCESSUS_HPP_
#define PROCESSUS_HPP_

#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

class Processus
{
private:
    pid_t _pid;
public:
    Processus(/* args */);
    ~Processus() = default;
    pid_t forkProcessus();
    pid_t getpid() const;
    int waitProcessus();
    void quit();
    bool isChild() const;
    bool isParent() const;
    static int waitPid(pid_t pid);
};

#endif /* !PROCESSUS_HPP_ */
