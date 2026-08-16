/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** RayTracerError
*/

#ifndef RAYTRACERERROR_HPP_
#define RAYTRACERERROR_HPP_

#include <exception>
#include <string>

class RayTracerError : public std::exception
{
    public:
        explicit RayTracerError(const std::string &message) : _message(message)
        {
        }

        ~RayTracerError() override = default;

        const char *what() const noexcept override
        {
            return _message.c_str();
        }

    private:
        std::string _message;
};

class ParsingError : public RayTracerError
{
    public:
        explicit ParsingError(const std::string &message) : RayTracerError(message)
        {
        }
};

class BuilderError : public RayTracerError
{
    public:
        explicit BuilderError(const std::string &message) : RayTracerError(message)
        {
        }
};

class FactoryError : public RayTracerError
{
    public:
        explicit FactoryError(const std::string &message) : RayTracerError(message)
        {
        }
};

#endif /* !RAYTRACERERROR_HPP_ */
