/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() : _user(nullptr)
{
    _position.resize(3);
}

Client::~Client()
{
}

User *Client::get_user()
{
    return _user;
}

void Client::set_user(User *user)
{
    _user = user;
}

std::vector<std::string> &Client::get_position()
{
    if (_position.size() < 3)
        _position.resize(3);
    return _position;
}

void Client::set_position(std::string name, std::size_t pos)
{
    _position[pos] = name;
}