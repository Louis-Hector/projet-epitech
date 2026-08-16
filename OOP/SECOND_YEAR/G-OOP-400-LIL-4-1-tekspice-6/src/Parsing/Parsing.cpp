/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** Parsing
*/

#include "Parsing.hpp"
#include "Factory.hpp"
#include "Execution.hpp"

Parsing::FILE_ERROR::FILE_ERROR(std::string msg) : _error(msg)
{

}

const char *Parsing::FILE_ERROR::what() const noexcept
{
    return _error.c_str();
}

static bool check_the_parts(const std::vector<std::string> &_line, bool &chip, bool &links, bool &haschip)
{
    if (_line.empty() || _line[0][0] == '#')
        return true;
    if (_line[0] == ".chipsets:") {
        chip = true;
        links = false;
        haschip = true;
        return true;
    }
    if (_line[0] == ".links:") {
        chip = false;
        links = true;
        return true;
    }
    return false;
}

void Parsing::recover_chips(const std::vector<std::string> &_line, Circuit &circuit)
{
    if (_line.size() != 2)
        throw FILE_ERROR("A component is invalid");
    if (circuit.searchComponent(_line[1]) == true)
        throw FILE_ERROR("Several components share the same name.");
    std::string _type = _line[0];
    std::string _name = _line[1];
    auto component = _factory.createComponent(_type);
    circuit.addComponent(_name, component, _type);
}

void Parsing::recover_links(const std::vector<std::string> &_line, Circuit &circuit)
{
    if (_line.size() != 2)
        throw FILE_ERROR("A component is invalid");
    std::string name1 = _line[0].substr(0, _line[0].find(':'));
    std::string name2 = _line[1].substr(0, _line[1].find(':'));
    if (circuit.searchComponent(name1) == false)
        throw FILE_ERROR("A component name is unknown '" + name1 + "'");
    if (circuit.searchComponent(name2) == false)
        throw FILE_ERROR("A component name is unknown '" + name2 + "'");
    std::string link1 = _line[0];
    std::string link2 = _line[1];
    circuit.addLinks(link1, link2);
    _factory.createLink(link1, link2, circuit);
}

void Parsing::read_file(Circuit &circuit)
{
    std::string current = "";
    std::string word = "";
    bool _chip = false;
    bool _links = false;
    bool haschip = false;

    while (std::getline(_file, current)) {
        current = current.substr(0, current.find('#'));
        std::vector<std::string> _line;
        std::stringstream ss(current);
        while (ss >> word)
            _line.push_back(word);
        if (check_the_parts(_line, _chip, _links, haschip))
            continue;
        if (_chip == true) {
            nb_component += 1;
            recover_chips(_line, circuit);
        }
        if (_links == true)
            recover_links(_line, circuit);
    }
    if (haschip == false || nb_component <= 0)
        throw FILE_ERROR("No chipsets in the circuit.");
}

void Parsing::open_file(char *file)
{
    _file = std::ifstream(file);
    if (!_file.is_open())
        throw std::runtime_error("Impossible to open the file");
}

int Parsing::launch_nts(int ac, char **av)
{
    Execution shell;

    try
    {
        if (ac != 2)
            throw std::runtime_error("Invalid args");
        open_file(av[1]);
        Circuit circuit;
        read_file(circuit);
        shell.launchShell(circuit);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}