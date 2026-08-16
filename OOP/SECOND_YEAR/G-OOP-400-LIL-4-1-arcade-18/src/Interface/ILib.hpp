/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** ILib
*/

#ifndef ILIB_HPP_
#define ILIB_HPP_

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

enum LibType {
    GAME,
    DISPLAY,
    UNDEFINE
};

class ILib
{
private:
public:
    virtual ~ILib() = default;
    virtual const std::string get_name() const = 0;
    virtual LibType get_type() const = 0;
};

#endif /* !ILIB_HPP_ */
