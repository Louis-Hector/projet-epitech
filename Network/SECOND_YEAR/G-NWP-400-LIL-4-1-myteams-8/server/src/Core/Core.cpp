/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Core
*/

#include "Core.hpp"

volatile std::sig_atomic_t sigint_received  = 0;

Core::Core(/* args */)
{
}

void Core::init_serv(int port)
{
    _serv_socket.InitSocket();
    struct sockaddr_in addr_server = {};

    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    addr_server.sin_addr.s_addr = INADDR_ANY;
    _serv_socket.bind(addr_server);
    _serv_socket.listen();
    return;
}

bool Core::remove_socket(std::size_t &pos_socket) 
{
    std::size_t max_socket = tab_clients.size() - 1;

    if (tab_clients[pos_socket].revents & (POLLERR | POLLHUP | POLLNVAL)) {
        _serv_socket.close_socket(tab_clients[pos_socket].fd);
        infos_client.erase(tab_clients[pos_socket].fd);
        if (max_socket != pos_socket) {
            tab_clients[pos_socket] = tab_clients.back();
            tab_clients.pop_back();
        }
        tab_clients[pos_socket].fd = -1;
        pos_socket -= 1;
        return true;
    }
    return false;
}

void signal_handler(int sig)
{
    if (sig == SIGINT)
        sigint_received = 1;
}

void Core::handle_action_client()
{
    for (std::size_t i = 1; i < tab_clients.size(); i++) {
        pos_socket = i;
        if (remove_socket(pos_socket) == true)
            continue;
        if (tab_clients[i].revents & POLLIN) {
            char buffer[1024] = {};
            ssize_t bytes = _serv_socket.read_socket(tab_clients[i].fd, buffer, sizeof(buffer));
            if (bytes == 0) {
                remove_socket(pos_socket);
                continue;
            }
            if (bytes == -1)
                continue;
            buffer[bytes] = '\0';
            read_command(buffer);
        }
    }
}

void Core::launch_poll()
{
    LoadSave folder("save");

    std::signal(SIGINT, signal_handler);
    folder.loadAll(data);
    data.users.reserve(1000);
    tab_clients.push_back({_serv_socket.getsocket(), POLLIN, 0});
    while (!sigint_received) {
        int value_poll = _serv_socket.poll(tab_clients, tab_clients.size());
        if (value_poll == -1) {
            if (errno == EINTR)
                continue;
            break;
        }
        if (tab_clients[0].revents & POLLIN) {
            struct sockaddr_in addr_client = {};
            socklen_t len = sizeof(addr_client);
            int fd_client = accept(tab_clients[0].fd, (struct sockaddr *)(&addr_client), &len);
            tab_clients.push_back({fd_client, POLLIN, 0});
            infos_client.insert({fd_client, {}});
            write(fd_client, (rfc_msg[NEW_CONNECTION].msg + "\r\n").c_str(), rfc_msg[NEW_CONNECTION].msg.size() + 2);
        }
        handle_action_client();
    }
    for (std::size_t i = 0; i < data.users.size(); i++)
        data.users[i].status = false;
    folder.saveAll(data);
}

void Core::read_command(char buffer[1024])
{
    std::string input(buffer);
    std::vector<std::string> args = {};

    std::size_t pos = input.find("\r\n");
    if (pos == std::string::npos)
        return;
    std::string line = input.substr(0, pos);
    std::stringstream ss(line);
    std::string command;
    ss >> command;
    if (command.size() == 0 || command[0] == '\"') {
        write(tab_clients[pos_socket].fd, (rfc_msg[INVALID_ARGS].msg + "\r\n").c_str(), rfc_msg[INVALID_ARGS].msg.size() + 2);
        return;
    } else
        args.push_back(command);
    std::string line_without_command;
    std::getline(ss, line_without_command);
    bool quote = false;
    std::string arg;
    for (size_t i = 0; i < line_without_command.size(); ++i) {
        if (line_without_command[i] == '"') {
            quote = !quote;
            if (!quote) {
                args.push_back(arg);
                arg.clear();
            }
        } else if (quote)
            arg += line_without_command[i];
        else if (!isspace(line_without_command[i])) {
            write(tab_clients[pos_socket].fd, (rfc_msg[NEED_QUOTE].msg + "\r\n").c_str(), rfc_msg[NEED_QUOTE].msg.size() + 2);
            return;
        }
    }
    if (quote) {
        write(tab_clients[pos_socket].fd, (rfc_msg[NEED_QUOTE].msg + "\r\n").c_str(), rfc_msg[NEED_QUOTE].msg.size() + 2);
        return;
    }
    if (args.size() == 0)  {
        write(tab_clients[pos_socket].fd, (rfc_msg[INVALID_ARGS].msg + "\r\n").c_str(), rfc_msg[INVALID_ARGS].msg.size() + 2);
        return;
    }
    launch_command(args);
}

void Core::launch_command(std::vector<std::string> &args)
{
    Server_Command instruct;
    int fd = tab_clients[pos_socket].fd;
    auto it_client = infos_client.find(fd);
    if (it_client == infos_client.end())
        return;
    const std::unordered_map<std::string, std::function<void(std::vector<std::string>&)>> commands = 
    {
        {"/help", [&](auto args) {instruct.help(args, fd);}},
        {"/login", [&](auto args) {instruct.login(args, fd, it_client->second, data.users, infos_client);}},
        {"/logout", [&](auto args) {instruct.logout(args, fd, it_client->second, infos_client, data.users);}},
        {"/users", [&](auto args) {instruct.users(args, fd, data.users);}},
        {"/user", [&](auto args) {instruct.user(args, fd, data.users);}},
        {"/send", [&](auto args) {instruct.send(args, fd, data.private_messages, infos_client, data.users);}},
        {"/messages", [&](auto args) {instruct.messages(args, fd, data.private_messages, it_client->second, data.users);}},
        {"/subscribe", [&](auto args) {instruct.subscribe(args, fd, data.teams, it_client->second, data.subscriptions, infos_client);}},
        {"/subscribed", [&](auto args) {instruct.subscribed(args, fd, it_client->second, data.subscriptions, data.users);}},
        {"/unsubscribe", [&](auto args) {instruct.unsubscribe(args, fd, data.teams, it_client->second, data.subscriptions, infos_client);}},
        {"/use", [&](auto args) {instruct.use(args, fd,it_client->second, data.teams, data.channels, data.threads);}},
        {"/create", [&](auto args) {instruct.create(args, fd, it_client->second, data.teams, data.channels, data.threads, data.replies, infos_client, data.subscriptions);}},
        {"/list", [&](auto args) {instruct.list(args, fd, it_client->second, data.teams, data.channels, data.threads, data.replies);}},
        {"/info", [&](auto args) {instruct.info(args, fd, it_client->second, data.teams, data.channels, data.threads);}}
    };
    auto elem = commands.find(args[0]);
    if (elem == commands.end()) {
        write(fd, (rfc_msg[INVALID_ARGS].msg + "\r\n").c_str(), rfc_msg[INVALID_ARGS].msg.size() + 2);
        return;
    }
    User *user = it_client->second.get_user();
    if ((elem->first != "/help" && elem->first != "/login") && (user == nullptr || user->status == false)) {
        write(fd, (rfc_msg[NOT_LOG].msg + "\r\n").c_str(), rfc_msg[NOT_LOG].msg.size() + 2);
        return;
    }
    elem->second(args);
    LoadSave save("save");
    save.saveAll(data);
    return;
}

int Core::start_serv(int port)
{
    try
    {
        init_serv(port);
        launch_poll();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return 84;
    } 
    return 0;
}