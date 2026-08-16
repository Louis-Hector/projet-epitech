/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <uuid/uuid.h>
#include <LoadSave.hpp>

class Client
{
private:
    User *_user;
    std::vector<std::string> _position;
public:
    Client();
    ~Client();
    void set_user(User *user);
    User *get_user();
    std::vector<std::string> &get_position();
    void set_position(std::string name, std::size_t pos);
};

#endif /* !CLIENT_HPP_ */
