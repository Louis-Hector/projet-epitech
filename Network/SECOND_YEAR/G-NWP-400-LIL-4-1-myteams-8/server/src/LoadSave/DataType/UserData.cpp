/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** UserData
*/

#include "UserData.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

extern "C" {
#include "logging_server.h"
}

UserData::UserData()
{
}

UserData::~UserData()
{
}

bool UserData::saveUsers(const std::vector<User> &users, std::string dirname)
{
    std::filesystem::create_directories(dirname);
    std::ofstream file(dirname + "/users.db");

    if (!file.is_open())
        return false;

    for (std::size_t i = 0; i < users.size(); i++) {
        file << users[i].uuid << "|"
             << users[i].name << "|"
             << users[i].status << "\n";
    }
    return true;
}

bool UserData::loadUsers(std::vector<User> &users, std::string dirname)
{
    std::ifstream file(dirname + "/users.db");
    std::string line;

    if (!file.is_open())
        return false;

    users.clear();

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string statusStr;
        User user;

        if (!std::getline(ss, user.uuid, '|'))
            continue;
        if (!std::getline(ss, user.name, '|'))
            continue;
        if (!std::getline(ss, statusStr, '|'))
            continue;

        user.status = std::atoi(statusStr.c_str());

        users.push_back(user);
        server_event_user_loaded(user.uuid.c_str(), user.name.c_str());
    }
    return true;
}
