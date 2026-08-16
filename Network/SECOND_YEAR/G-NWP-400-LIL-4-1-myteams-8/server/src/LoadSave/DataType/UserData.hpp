/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** UserData
*/

#ifndef USERDATA_HPP_
#define USERDATA_HPP_

#include <string>
#include <vector>

struct User {
    std::string uuid;
    std::string name;
    bool status;
};

class UserData {
    public:
        UserData();
        ~UserData();

        bool saveUsers(const std::vector<User> &users, std::string _dirname);
        bool loadUsers(std::vector<User> &users, std::string _dirname);

    protected:
    private:
};

#endif /* !USERDATA_HPP_ */
