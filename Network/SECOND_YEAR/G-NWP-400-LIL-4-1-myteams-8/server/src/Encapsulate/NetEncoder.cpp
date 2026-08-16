/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** NetEncoder
*/

#include "NetEncoder.hpp"
#include <unistd.h>


NetEncoder::NetEncoder()
{
}

NetEncoder::C_ERROR::C_ERROR(std::string error) : _msg(error)
{
}

const char *NetEncoder::C_ERROR::what() const noexcept
{
    return _msg.c_str();
}

NetEncoder::~NetEncoder()
{
    if (_socket != -1)
        close(_socket);
}

void NetEncoder::InitSocket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0); 
    if (_socket == -1)
        throw C_ERROR("Server Socket fail"); 
}

int NetEncoder::getsocket()
{
    return _socket;
}

uint16_t NetEncoder::htons(int port)
{
    return ::htons(port);
}

void NetEncoder::bind(struct sockaddr_in _addr)
{
    if (::bind(_socket, (struct sockaddr *)(&_addr), sizeof(_addr)) == -1)
        throw C_ERROR("Impossible to bind the adress to server");
}

void NetEncoder::listen()
{
    if (::listen(_socket, 10000))
        throw C_ERROR("Cannot listen the new data connections");
}

int NetEncoder::poll(std::vector<struct pollfd> &tab_clients, int nb_sockets)
{
    return ::poll(tab_clients.data(), nb_sockets, -1);
}

void NetEncoder::close_socket(int socket)
{
    if (socket != -1)
        close(socket);
}

ssize_t NetEncoder::read_socket(int socket, char *buffer, int size)
{
    return read(socket, buffer, size);
}