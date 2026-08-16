/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Log
*/

#ifndef LOG_HPP_
#define LOG_HPP_

#include <fstream>
#include <iostream>
#include "Mutex.hpp"

class Log
{
private:
    std::ofstream _file;
    Mutex _mutex;
public:
    Log();
    ~Log();
    void write_log(const std::string &content);
}; extern Log logger;

#endif /* !LOG_HPP_ */
