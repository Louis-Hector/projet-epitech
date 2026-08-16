/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Parsing_client
*/

#include "Parsing_client.hpp"
#include <vector>
#include <string>
#include <sstream>

Parsing_client::Parsing_client(/* args */)
{
}

Parsing_client::ARGS_ERROR::ARGS_ERROR(std::string error) : _msg(error)
{
}

const char *Parsing_client::ARGS_ERROR::what() const noexcept
{
    return _msg.c_str();
}


void Parsing_client::print_help()
{
    std::cout << "USAGE: ./myteams_cli ip port" << std::endl << std::endl;
    std::cout << " ip is the server ip address on which the server socket listens." << std::endl;
    std::cout << " port is the port number on which the server socket listens." << std::endl;
}

int Parsing_client::connect_to_server()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        throw ARGS_ERROR("socket fail");
    sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);

    if (inet_pton(AF_INET, _ip.c_str(), &addr.sin_addr) <= 0)
        throw ARGS_ERROR("inet_pton fail");
    if (connect(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        close(fd);
        throw ARGS_ERROR("connect fail");
    }
    return fd;
}

bool Parsing_client::is_ipv4(char* addr)
{
    int a;
    int b;
    int c;
    int d;
    char end;

    if (!addr || addr[0] == '\0')
        return false;
    if (sscanf(addr, "%3d.%3d.%3d.%3d%c", &a, &b, &c, &d, &end) != 4)
        return false;
    if (a < 0 || a > 255)
        return false;
    if (b < 0 || b > 255)
        return false;
    if (c < 0 || c > 255)
        return false;
    if (d < 0 || d > 255)
        return false;
    return true;
}


void Parsing_client::check_args(char *addr, char *port)
{
    if (!is_ipv4(addr))
        throw ARGS_ERROR("The address: '" + std::string(addr) + "' does not feat the ipv4 format");
    for (std::size_t i = 0; port[i] != '\0'; i++)
        if (port[i] < '0' || port[i] > '9')
            throw ARGS_ERROR("The port: '" + std::string(port) + "' is not a number");
    _port = std::stoi(port);
    if (_port < 1 || _port > 65535)
        throw ARGS_ERROR("The port: '" + std::string(port) + "' is out of range (port must be between 1 and 65535)");
    _ip = addr;
    return;
}

int Parsing_client::parse_args(int ac, char **av)
{
    try
    {
        if (ac == 2 && std::string(av[1]) == "--help") {
            print_help();
            return 0;
        }
        if (ac < 3) {
            throw ARGS_ERROR("Too few arguments");
        }
        if (ac > 3) {
            throw ARGS_ERROR("Too much arguments");
        }
        char *addr = av[1];
        char *port = av[2];
        check_args(addr, port);
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
        return 84;
    }
    return 0;
}

void Parsing_client::send_command(int fd, const std::string& msg)
{
    std::string command = msg + "\r\n";
    ssize_t total = 0;
    ssize_t size = command.size();

    while (total < size) {
        ssize_t sent = write(fd, command.c_str() + total, size - total);
        if (sent < 0)
            throw ARGS_ERROR("write failed");
        total += sent;
    }
    return;
}

std::string Parsing_client::read_from_server(int fd)
{
    char buffer[1024];
    ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes < 0)
        throw ARGS_ERROR("read failed");
    if (bytes == 0)
        throw ARGS_ERROR("connection closed");

    buffer[bytes] = '\0';
    return std::string(buffer);
}

bool Parsing_client::extract_message(std::string &buffer, std::string &message)
{
    std::size_t pos = buffer.find("\r\n");

    if (pos == std::string::npos)
        return false;
    message = buffer.substr(0, pos);
    buffer.erase(0, pos + 2);
    return true;
}