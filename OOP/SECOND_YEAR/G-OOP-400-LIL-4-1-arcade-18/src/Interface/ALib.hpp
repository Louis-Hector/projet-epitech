/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** ALib
*/

#ifndef ALIB_HPP_
#define ALIB_HPP_

#include "ILib.hpp"

class ALib : public ILib
{
private:
protected:
    std::string _name = "Undefined";
    LibType _type = LibType::UNDEFINE;
public:
    ALib() = default;
    virtual ~ALib() = default;
    const std::string get_name() const override;
    LibType get_type() const override;
};

#endif /* !ALIB_HPP_ */
