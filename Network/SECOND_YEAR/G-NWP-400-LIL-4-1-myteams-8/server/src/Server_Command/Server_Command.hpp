/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Server_Command
*/

#ifndef SERVER_COMMAND_HPP_
#define SERVER_COMMAND_HPP_
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

#include <vector>
#include <iostream>
#include <string>
#include "help.hpp"
#include "Rfc.hpp"
#include <unistd.h>
#include "Client.hpp"
#include "LoadSave.hpp"
#include <unordered_map>
#include <ctime>

class Server_Command
{
private:
    /* data */
public:
    Server_Command(/* args */);
    ~Server_Command();
    bool check_args(std::vector<std::string> &args, int fd, std::size_t min, std::size_t max);
    void help(std::vector<std::string> &args, int fd);
    void login(std::vector<std::string> &args, int fd, Client &client, std::vector<User> &users, std::unordered_map<int, Client> &clients);
    void logout(std::vector<std::string> &args, int fd, Client &client, std::unordered_map<int, Client> &clients, std::vector<User> &users);
    void users(std::vector<std::string> &args, int fd, std::vector<User> &users);
    void user(std::vector<std::string> &args, int fd, std::vector<User> &users);
    void send(std::vector<std::string> &args, int fd, std::vector<PrivateMessage> &msg_priv, std::unordered_map<int, Client> &clients, std::vector<User> &users);
    void messages(std::vector<std::string> &args, int fd, std::vector<PrivateMessage> &msg_priv, Client &client, std::vector<User> &users);
    void subscribe(std::vector<std::string> &args, int fd, std::vector<Team> &teams, Client &client, std::vector<Subscription> &sub, std::unordered_map<int, Client> &clients);
    void subscribed(std::vector<std::string> &args, int fd, Client &client, std::vector<Subscription> &sub, std::vector<User> &users);
    void unsubscribe(std::vector<std::string> &args, int fd, std::vector<Team> &teams, Client &client, std::vector<Subscription> &sub, std::unordered_map<int, Client> &clients);
    void use(std::vector<std::string> &args, int fd, Client &client, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads);
    void create(std::vector<std::string> &args, int fd, Client &client, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads, std::vector<Reply> &replies, std::unordered_map<int, Client> &clients, std::vector<Subscription> &sub);
    void list(std::vector<std::string> &args, int fd, Client &client, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads, std::vector<Reply> &replies);
    void info(std::vector<std::string> &args, int fd, Client &client, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads);
};

#endif /* !SERVER_COMMAND_HPP_ */
