/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "NetEncoder.hpp"
#include "Server_Command.hpp"
#include "Client.hpp"
#include "Rfc.hpp"
#include "LoadSave.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <unistd.h>
#include <csignal>

class Core
{
private:
    NetEncoder _serv_socket;
    std::size_t pos_socket = {};
    std::vector<pollfd> tab_clients = {};
    std::unordered_map<int, Client> infos_client = {};
    SaveData data = {};
public:
    Core(/* args */);
    void init_serv(int port);
    int start_serv(int port);
    void launch_poll();
    void handle_action_client();
    bool remove_socket(std::size_t &pos_socket);
    void read_command(char buffer[1024]);
    void launch_command(std::vector<std::string> &args);
};

#endif /* !CORE_HPP_ */
