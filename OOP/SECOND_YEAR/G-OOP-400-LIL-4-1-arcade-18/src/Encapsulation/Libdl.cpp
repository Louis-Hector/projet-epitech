/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Libdl
*/

#include "Libdl.hpp"

Libdl::Libdl(/* args */) : _handle()
{
}

Libdl::~Libdl()
{
    close_lib();
}

bool Libdl::open_lib(const char *path_lib) 
{
    if (_handle)
        close_lib();
    _handle = dlopen(path_lib, RTLD_LAZY | RTLD_GLOBAL);
    if (!_handle) {
        fprintf(stderr, "Erreur dlopen: %s\n", dlerror());
        return false;
    }
    return true;
}

void *Libdl::search_elem(const char *name_function)
{
    if (!_handle)
        return NULL;
    dlerror();
    void *elem = dlsym(_handle, name_function);
    auto error = dlerror();
    if (error != NULL)
        return NULL;
    return elem;
}

void Libdl::close_lib()
{
    if (_handle) {
        dlclose(_handle);
        _handle = NULL;
    }
}
