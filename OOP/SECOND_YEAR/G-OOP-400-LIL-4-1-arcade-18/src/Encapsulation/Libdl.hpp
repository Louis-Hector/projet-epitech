/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Libdl
*/

#ifndef LIBDL_HPP_
#define LIBDL_HPP_

#include <dlfcn.h>
#include "IDisplay.hpp"
#include "IGame.hpp"

class Libdl
{
private:
    void * _handle;
public:
    Libdl(/* args */);
    ~Libdl();
    bool open_lib(const char *path_lib);
    void *search_elem(const char *name_function);
    void close_lib();
};


#endif /* !LIBDL_HPP_ */
