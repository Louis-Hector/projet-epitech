/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** Log
*/

#include "Log.hpp"
#include "ScopedLock.hpp"

Log::Log() : _file("log.txt", std::ios::out | std::ios::trunc)
{
    if (!_file)
        std::cerr << "Not possible to create the file for the log" << std::endl;
}

Log::~Log()
{
    if (_file)
        _file.close();
}

void Log::write_log(const std::string &content)
{
    ScopedLock lock(_mutex);
    std::cout << content << std::endl;
    if (_file)
        _file << content << std::endl;
}

Log logger;