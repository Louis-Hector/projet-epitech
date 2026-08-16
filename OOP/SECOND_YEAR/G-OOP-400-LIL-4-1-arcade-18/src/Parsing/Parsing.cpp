/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Parsing
*/

#include "Parsing.hpp"

bool Parsing::can_launch_graphic()
{
    std::string display = std::getenv("DISPLAY") ? std::getenv("DISPLAY") : "";

    return !display.empty();
}

Parsing::Parsing(/* args */)
{
}

Parsing::FILE_ERROR::FILE_ERROR(std::string msg) : _error(msg)
{
}

const char *Parsing::FILE_ERROR::what() const noexcept 
{
    return _error.c_str();
}

void Parsing::check_lib(char *path_lib)
{
    Libdl dl;

    if (dl.open_lib(path_lib) == false)
        throw FILE_ERROR("Cannot open the first lib graphic");
    auto module = (ILib *(*)())dl.search_elem("entryPoint");
    if (module == NULL)
        throw FILE_ERROR("Error searching for the entryPoint function");
    auto value = module();
    if (!value) {
        dl.close_lib();
        throw FILE_ERROR("Error: entryPoint returned null for " + std::string(path_lib));
    }
    LibType type = value->get_type();
    delete value;
    dl.close_lib();
    if (type != LibType::DISPLAY)
        throw FILE_ERROR("Error: " + std::string(path_lib) + " not a graphical library");
    _parse_librarys.push_back(path_lib);
    return;
}

void Parsing::open_folder_lib(char *first_args)
{
    const std::string first_lib = first_args ? std::string(first_args) : "";

    if (!std::filesystem::exists("./lib") || !std::filesystem::is_directory("./lib"))
        return;
    for (const auto &Entry : std::filesystem::directory_iterator("./lib"))  {
        if (Entry.is_directory())
            continue;
        auto file = Entry.path().string();
        auto pos_extension = file.find_last_of('.');
        if (pos_extension == std::string::npos || file.substr(pos_extension + 1) != "so")
            continue;
        if (first_lib == file)
            continue;
        if (Entry.is_regular_file()) {
            Libdl dl;
            if (dl.open_lib(file.c_str()) == false)
                continue;
            auto module = (ILib *(*)(void))dl.search_elem("entryPoint");
            if (module == NULL) {
                dl.close_lib();
                continue;
            }
            auto value = module();
            if (!value) {
                dl.close_lib();
                continue;
            }
            LibType name_class = value->get_type();
            if (name_class == LibType::DISPLAY)
                _parse_librarys.push_back(file);
            if (name_class == LibType::GAME)
                _parse_games.push_back(file);
            delete value;
            dl.close_lib();
        }
    }
        
}

int Parsing::parse_args(int ac, char **av)
{
    try
    {
        if (ac != 2 || av[1] == NULL)
            throw FILE_ERROR("The number of arguments is invalid.");
        if (!can_launch_graphic())
            throw FILE_ERROR("Error: Arcade cannot be loaded in TTY or without DISPLAY");
        check_lib(av[1]);
        open_folder_lib(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}
