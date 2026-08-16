/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Server_Command
*/

#include "Server_Command.hpp"

extern "C" {
#include "logging_server.h"
}

Server_Command::Server_Command(/* args */)
{
}

Server_Command::~Server_Command()
{
}

bool Server_Command::check_args(std::vector<std::string> &args, int fd, std::size_t min, std::size_t max)
{
    if (args.size() < min) {
        write(fd, (rfc_msg[NOT_ENOUGH_ARGS].msg + "\r\n").c_str(), rfc_msg[NOT_ENOUGH_ARGS].msg.size() + 2);
        return true;
    }
    if (args.size() > max) {
        write(fd, (rfc_msg[TOO_MANY_ARGS].msg + "\r\n").c_str(), rfc_msg[TOO_MANY_ARGS].msg.size() + 2);
        return true; 
    }
    return false;
}

void Server_Command::help(std::vector<std::string> &args, int fd)
{
    if (args.size() == 1) {
        for (std::size_t i = 0; i < help_msg.size(); i++)
            write(fd, help_msg[i].name.c_str(), help_msg[i].name.size());
        write(fd, (rfc_msg[COMMAND_VALID].msg + "\r\n").c_str(), rfc_msg[COMMAND_VALID].msg.size() + 2);
        return;
    }
    if (check_args(args, fd, 1, 2) == true)
        return;
    std::size_t index_command = {};
    if (args.size() == 2) {
        for (std::size_t i = 0; i < help_msg.size(); i++) {
            if (help_msg[i].name == args[1] + "\n") {
                index_command = i;
                break;
            }
        }
        write(fd, help_msg[index_command].name.c_str(), help_msg[index_command].name.size());
        write(fd, help_msg[index_command].description.c_str(), help_msg[index_command].description.size());
        write(fd, help_msg[index_command].body.c_str(), help_msg[index_command].body.size());
    }
    write(fd, (rfc_msg[COMMAND_VALID].msg + "\r\n").c_str(), rfc_msg[COMMAND_VALID].msg.size() + 2);
}

static User* recover_user(std::vector<User> &users, const std::string &name_user)
{
    char uuid_string[37] = {};
    uuid_t value = {};

    for (std::size_t i = 0; i < users.size(); i++) {
        if (users[i].name == name_user) {
            users[i].status = true;
            return &users[i];
        }
    }
    User new_user = {};
    new_user.name = name_user;
    uuid_generate(value);
    uuid_unparse(value, uuid_string);
    new_user.uuid = uuid_string;
    new_user.status = true;
    users.push_back(new_user);
    server_event_user_created(new_user.uuid.c_str(), new_user.name.c_str());
    return &users.back();
}

void Server_Command::login(std::vector<std::string> &args, int fd, Client &client, std::vector<User> &users, std::unordered_map<int, Client> &clients)
{
    if (check_args(args, fd, 2, 2) == true)
        return;
    std::string name_user = args[1];
    if (name_user.size() > MAX_NAME_LENGTH) {
        write(fd, rfc_msg[NAME_LENGHT].msg.c_str(), rfc_msg[NAME_LENGHT].msg.size());
        return;
    }
    User *user = recover_user(users, name_user);
    client.set_user(user);
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if (it->second.get_user() && it->second.get_user()->status == true) {
            std::string msg = rfc_msg[LOGIN].msg + "|" + user->uuid + "|" + user->name + "\r\n";
            write(it->first, msg.c_str(), msg.size());
        }
    }
    server_event_user_logged_in(user->uuid.c_str());
    return;
}


void Server_Command::logout(std::vector<std::string> &args, int fd, Client &client, std::unordered_map<int, Client> &clients, std::vector<User> &users)
{
    if (check_args(args, fd, 1, 1))
        return;
    User *user = client.get_user();
    if (user == nullptr)
        return;
    user->status = false;
    for (auto it = users.begin(); it != users.end(); it++) {
        if (it->uuid == user->uuid) {
            it->status = false;
            break;
        }
    }
    server_event_user_logged_out(user->uuid.c_str());
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if (it->second.get_user() && user->uuid != it->second.get_user()->uuid && it->second.get_user()->status == true) {
            std::string msg = rfc_msg[LOGOUT].msg + "|" + user->uuid + "|" + user->name + "\r\n";
            write(it->first, msg.c_str(), msg.size());
        }
    }
    std::string msg = rfc_msg[LOGOUT].msg + "|" + user->uuid + "|" + user->name + "\r\n";
    write(fd, msg.c_str(), msg.size());
    client.set_user(nullptr);
}

void Server_Command::users(std::vector<std::string> &args, int fd, std::vector<User> &users)
{
    if (check_args(args, fd, 1, 1) == true)
        return;
    for (std::size_t i = 0; i < users.size(); i++) {
        std::string msg = rfc_msg[USERS].msg + "|" + users[i].uuid + "|" + users[i].name + "|" + (users[i].status == true ? "1" : "0") + "\r\n";
        write(fd, msg.c_str(), msg.size());
    }
    return;
}

void Server_Command::user(std::vector<std::string> &args, int fd, std::vector<User> &users)
{
    if (check_args(args, fd, 2, 2) == true)
        return;
    std::string msg;
    User *user = nullptr;
    for (std::size_t i = 0; i < users.size(); i++) {
        if (users[i].uuid == args[1]) {
            user = &users[i];
            break;
        }
    }
    if (!user) {
        std::string msg = rfc_msg[UNKNOWN_USER].msg + "|" + args[1] + "\r\n";
        write(fd, msg.c_str(), msg.size());
        return;
    }
    msg = rfc_msg[USER].msg + "|" + user->uuid + "|" + user->name + "|" + (user->status == true ? "1" : "0") + "\r\n";
    write(fd, msg.c_str(), msg.size());
    return;
}

void Server_Command::send(std::vector<std::string> &args, int fd, std::vector<PrivateMessage> &msg_priv, std::unordered_map<int, Client> &clients, std::vector<User> &users)
{
    if (check_args(args, fd, 3, 3) == true)
        return;
    if (args[2].size() > MAX_BODY_LENGTH) {
        write(fd, (rfc_msg[BODY_LENGHT].msg + "\r\n").c_str(), rfc_msg[BODY_LENGHT].msg.size() + 2);
        return;
    }
    auto sender = clients.find(fd);
    if (sender == clients.end() || sender->second.get_user() == nullptr) {
        write(fd, (rfc_msg[NOT_LOG].msg + "\r\n").c_str(), rfc_msg[NOT_LOG].msg.size() + 2);
        return;
    }
    bool user_exist = false;
    for (const auto &user : users)
        if (user.uuid == args[1])
            user_exist = true;
    if (user_exist == false) {
        std::string msg = rfc_msg[UNKNOWN_USER].msg + "|" + args[1] + "\r\n";
        write(fd, msg.c_str(), msg.size());
        return;
    }
    PrivateMessage msg_actual = {sender->second.get_user()->uuid, args[1], time(NULL),  args[2]};
    msg_priv.push_back(msg_actual);
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if (it->second.get_user()->uuid == msg_actual.receiver_uuid) {
            std::string msg = rfc_msg[SEND].msg + "|" +  msg_actual.sender_uuid + "|" + msg_actual.body + "\r\n";
            write(it->first, msg.c_str(), msg.size());
            break;
        }
    }   
    server_event_private_message_sended(sender->second.get_user()->uuid.c_str(), msg_actual.receiver_uuid.c_str(), msg_actual.body.c_str());
    return;
}

void Server_Command::messages(std::vector<std::string> &args, int fd, std::vector<PrivateMessage> &msg_priv, Client &client, std::vector<User> &users)
{
    if (check_args(args, fd, 2, 2) == true)
        return;
    if (client.get_user() == nullptr) {
        write(fd, (rfc_msg[NOT_LOG].msg + "\r\n").c_str(), rfc_msg[NOT_LOG].msg.size() + 2);
        return;
    }
    bool user_exist = false;
    for (const auto &user : users)
        if (user.uuid == args[1])
            user_exist = true;
    if (user_exist == false) {
        std::string msg = rfc_msg[UNKNOWN_USER].msg + "|" + args[1] + "\r\n";
        write(fd, msg.c_str(), msg.size());
        return;
    }
    for (std::size_t i = 0; i < msg_priv.size(); i++) {
        std::string msg = "";
        if (msg_priv[i].sender_uuid == client.get_user()->uuid && msg_priv[i].receiver_uuid == args[1]) {
            msg = rfc_msg[MESSAGES].msg + "|" + msg_priv[i].sender_uuid + "|" + std::to_string(msg_priv[i].timestamp) + "|" + msg_priv[i].body + "\r\n";
            write(fd,  msg.c_str(), msg.size());
        } else if (msg_priv[i].sender_uuid == args[1] && msg_priv[i].receiver_uuid == client.get_user()->uuid) {
            msg = rfc_msg[MESSAGES].msg + "|" + msg_priv[i].sender_uuid + "|" + std::to_string(msg_priv[i].timestamp) + "|" + msg_priv[i].body + "\r\n";
            write(fd, msg.c_str(), msg.size());
        }
    }
    return;
}

static bool check_team_exist(int fd, std::vector<std::string> &args, std::vector<Team> &teams, Client &client, Team &your_team)
{
    bool team_exist = false;
    for (const auto &team : teams) {
        if (team.uuid == args[1]) {
            team_exist = true;
            your_team = team;
            break;
        }
    }
    if (team_exist == false) {
        std::string msg = rfc_msg[USER_ERROR].msg + "|" + client.get_user()->uuid + "\r\n";
        write(fd, msg.c_str(), msg.size());
        return true;
    }
    return false;
}

void Server_Command::subscribe(std::vector<std::string> &args, int fd, std::vector<Team> &teams, Client &client, std::vector<Subscription> &sub, std::unordered_map<int, Client> &clients)
{
    if (check_args(args, fd, 2, 2) == true)
        return;
    Team your_team = {};
    if (check_team_exist(fd, args, teams, client, your_team) == true)
        return;
    bool already_sb = false;
    for (const auto &sb : sub) {
        if (your_team.uuid == sb.team_uuid && client.get_user()->uuid == sb.user_uuid) {
            already_sb = true;
            break;
        }
    }
    if (already_sb == true) {
        write(fd, (rfc_msg[ALREADY_SUB].msg + "\r\n").c_str(), rfc_msg[ALREADY_SUB].msg.size() + 2);
        return;
    }
    sub.push_back({client.get_user()->uuid, your_team.uuid});
    std::string msg = rfc_msg[SUBSCRIBE].msg + "|" + client.get_user()->uuid + "|" + your_team.uuid + "\r\n";
    write(fd, msg.c_str(), msg.size());
    for (const auto &sb : sub) {
        if (your_team.uuid == sb.team_uuid && sb.user_uuid != client.get_user()->uuid) {
            for (auto it = clients.begin(); it != clients.end(); it++) {
                if (it->second.get_user() && it->second.get_user()->status == true && it->second.get_user()->uuid == sb.user_uuid) {
                    std::string msg = rfc_msg[NOTIFY_OTHER].msg + " join the team\r\n";
                    write(it->first, msg.c_str(), msg.size());
                }
            }
        }
    }
    server_event_user_subscribed(args[1].c_str(), client.get_user()->uuid.c_str());
}

void Server_Command::subscribed(std::vector<std::string> &args, int fd, Client &client, std::vector<Subscription> &sub, std::vector<User> &users)
{
    if (check_args(args, fd, 1, 2) == true)
        return;
    if (args.size() == 1) {
        for (const auto &sb : sub) {
            if (sb.user_uuid == client.get_user()->uuid) {
                std::string msg = rfc_msg[LIST_SUB].msg + "|" + sb.team_uuid + "\r\n";
                write(fd, msg.c_str(), msg.size());
            }
        }
    } else {
        for (const auto &sb : sub) {
            if (args[1] == sb.team_uuid) {
                for (auto it = users.begin(); it != users.end(); it++) {
                    if (it->uuid == sb.user_uuid) {
                        std::string msg = rfc_msg[LIST_SUB].msg + "|" + sb.user_uuid + "\r\n";
                        write(fd, msg.c_str(), msg.size());
                    }
                }
            }
        }
    }
}

void Server_Command::unsubscribe(std::vector<std::string> &args, int fd, std::vector<Team> &teams, Client &client, std::vector<Subscription> &sub, std::unordered_map<int, Client> &clients)
{
    if (check_args(args, fd, 2, 2) == true)
        return;
    Team your_team = {};
    if (check_team_exist(fd, args, teams, client, your_team) == true)
        return;
    bool already_sb = false;
    auto location_erase = sub.end();
    for (auto it = sub.begin(); it != sub.end(); it++) {
        if (your_team.uuid == it->team_uuid && client.get_user()->uuid == it->user_uuid) {
            location_erase = it;
            already_sb = true;
            break;
        }
    }
    if (already_sb == false) {
        write(fd, (rfc_msg[ALREADY_SUB].msg + "\r\n").c_str(), rfc_msg[ALREADY_SUB].msg.size() + 2);
        return;
    }
    sub.erase(location_erase);
    std::string msg = rfc_msg[UNSUBSCRIBE].msg + "|" + client.get_user()->uuid + "|" + your_team.uuid + "\r\n";
    write(fd, msg.c_str(), msg.size());
    for (const auto &sb : sub) {
        if (your_team.uuid == sb.team_uuid && sb.user_uuid != client.get_user()->uuid) {
            for (auto it = clients.begin(); it != clients.end(); it++) {
                if (it->second.get_user() && it->second.get_user()->status == true && it->second.get_user()->uuid == sb.user_uuid) {
                    std::string msg = rfc_msg[NOTIFY_OTHER].msg + " quit the team\r\n";
                    write(it->first, msg.c_str(), msg.size());
                }
            }
        }
    }
    server_event_user_unsubscribed(args[1].c_str(), client.get_user()->uuid.c_str());
}

static void recover_channel_thread(std::vector<std::string> &args, int fd, std::vector<Thread> &threads, std::vector<std::string> &context, std::vector<Channel> &channels)
{
    if (args.size() > 2) {
        bool channel_exist = false;
        for (const auto &channel : channels) {
            if (channel.team_uuid == context[0] && channel.uuid == args[2]) {
                context[1] = args[2];
                channel_exist = true;
                break;
            }
        }
        if (channel_exist == false) {
            write(fd, (rfc_msg[NOT_LOCATION].msg + "\r\n").c_str(), rfc_msg[NOT_LOCATION].msg.size() + 2);
            return;
        }
    }
    if (args.size() > 3) {
        bool thread_exist = false;
        for (const auto &thread : threads) {
            if (thread.channel_uuid == context[1] && thread.uuid == args[3]) {
                context[2] = args[3];
                thread_exist = true;
                break;
            }
        }
        if (thread_exist == false) {
            write(fd, (rfc_msg[NOT_LOCATION].msg + "\r\n").c_str(), rfc_msg[NOT_LOCATION].msg.size() + 2);
            return;
        }
    }
}

void Server_Command::use(std::vector<std::string> &args, int fd, Client &client, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads)
{
    if (check_args(args, fd, 1, 4))
        return;
    std::vector<std::string> &context = client.get_position();
    context[0].clear();
    context[1].clear();
    context[2].clear();
    if (args.size() == 1) {
        write(fd, rfc_msg[COMMAND_VALID].msg.c_str(), rfc_msg[COMMAND_VALID].msg.size());
        return;
    }
    bool team_exist = false;
    for (const auto &team : teams) {
        if (team.uuid == args[1]) {
            context[0] = args[1];
            team_exist = true;
            break;
        }
    }
    if (team_exist == false) {
        write(fd, (rfc_msg[NOT_LOCATION].msg + "\r\n").c_str(), rfc_msg[NOT_LOCATION].msg.size() + 2);
        return;
    }
    recover_channel_thread(args, fd, threads, context, channels);
    return;
}

static std::string generate_uuid_context()
{
    uuid_t uuid_generation = {};
    char uuid_string[37] = {};
    uuid_generate(uuid_generation);
    uuid_unparse(uuid_generation, uuid_string);
    return uuid_string;
}

static bool check_already_create(std::vector<std::string> &args, int fd, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads, std::vector<std::string> &contexts)
{
    if (contexts[0].empty()) {
        for (const auto &team : teams) {
            if (team.name == args[1]) {
                std::string msg = rfc_msg[TEAM_ERROR].msg + "|" + team.uuid + "\r\n";
                write(fd, msg.c_str(), msg.size());
                return true;
            }
        }
    }
    else if (contexts[1].empty()) {
        for (const auto &channel : channels) {
            if (channel.name == args[1]) {
                std::string msg = rfc_msg[CHANNEL_ERROR].msg + "|" + channel.uuid + "\r\n";
                write(fd, msg.c_str(), msg.size());
                return true;
            }
        }
    }
    else if (contexts[2].empty()) {
        for (const auto &thread : threads) {
            if (thread.title == args[1]) {
                std::string msg = rfc_msg[THREAD_ERROR].msg + "|" + thread.uuid + "\r\n";
                write(fd, msg.c_str(), msg.size());
                return true;
            }
        }
    }
    return false;
}

static void create_message(const std::string& type, const std::string& uuid, const std::string& name
    , const std::string& description, int fd, bool is_thread, bool is_reply, time_t timestamp, const std::string &user_uuid) 
{
    std::string msg = "";
    if (is_thread == false && is_reply == false)
        msg = type + "|" + uuid + "|" + name + "|" + description + "\r\n";
    if (is_thread == true)
        msg = type + "|" + uuid + "|" + user_uuid + "|" + std::to_string(timestamp) + "|" + name + "|" + description + "\r\n";
    if (is_reply == true)
        msg = type + "|" + uuid + "|" + user_uuid + "|" + std::to_string(timestamp) + "|" + description + "\r\n";
    write(fd, msg.c_str(), msg.size());
}

void Server_Command::create(std::vector<std::string> &args, int fd, Client &client, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads, std::vector<Reply> &replies, std::unordered_map<int, Client> &clients, std::vector<Subscription> &sub)
{
    std::vector<std::string> &context = client.get_position();
    bool number_of_arguments = context[2].empty();

    if (number_of_arguments == true) {
        if (check_args(args, fd, 3, 3))
            return;
        if (args[2].size() > MAX_DESCRIPTION_LENGTH) {
            write(fd, rfc_msg[DESCRIPTION_LENGHT].msg.c_str(), rfc_msg[DESCRIPTION_LENGHT].msg.size());
            return;
        }
    }
    if (check_already_create(args, fd, teams, channels, threads, context) == true)
        return;
    std::string uuid = generate_uuid_context();
    if (context[0].empty()) {
        teams.push_back({uuid, args[1], args[2], client.get_user()->uuid});
        sub.push_back({client.get_user()->uuid, teams.back().uuid});
        for (auto it = clients.begin(); it != clients.end(); it++)
            if (it->second.get_user() && it->second.get_user()->status == true)
                create_message(rfc_msg[CREATE_TEAM].msg, uuid, args[1], args[2], it->first, false, false, NULL, "");
        server_event_team_created(uuid.c_str(), args[1].c_str(), client.get_user()->uuid.c_str());
    } else if (context[1].empty()) {
        channels.push_back({uuid, context[0], args[1], args[2]});
        for (const auto &s : sub)
            if (s.team_uuid == context[0])
                for (auto it = clients.begin(); it != clients.end(); it++)
                    if (it->second.get_user() && it->second.get_user()->status == true && it->second.get_user()->uuid == s.user_uuid)
                        create_message(rfc_msg[CREATE_CHANNEL].msg, uuid, args[1], args[2], it->first, false, false, NULL, "");
        server_event_channel_created(context[0].c_str(), uuid.c_str(), args[1].c_str());
    } else if (context[2].empty()) {
        threads.push_back({uuid, context[1], client.get_user()->uuid, time(NULL), args[1], args[2]});
        for (const auto &s : sub) {
            if (s.team_uuid == context[0]) {
                for (auto it = clients.begin(); it != clients.end(); it++)
                    if (it->second.get_user() && it->second.get_user()->status == true && it->second.get_user()->uuid == s.user_uuid)
                        create_message(rfc_msg[CREATE_THREAD].msg, uuid, args[1], args[2], it->first, true, false, threads.back().timestamp, threads.back().user_uuid);
            }
        }
        server_event_thread_created(context[1].c_str(), uuid.c_str(), client.get_user()->uuid.c_str(), args[1].c_str(), args[2].c_str());
    } else {
        replies.push_back({context[2], client.get_user()->uuid, time(NULL), args[1]});
        for (const auto &s : sub) {
            if (s.team_uuid == context[0]) {
                for (auto it = clients.begin(); it != clients.end(); it++)
                    if (it->second.get_user() && it->second.get_user()->status == true && it->second.get_user()->uuid == s.user_uuid)
                        create_message(rfc_msg[CREATE_REPLY].msg, replies.back().thread_uuid, "", args[1], it->first, false, true, replies.back().timestamp, replies.back().user_uuid);
            }
        }
        server_event_reply_created(context[2].c_str(), client.get_user()->uuid.c_str(), args[1].c_str());
    }
}
 
void Server_Command::list(std::vector<std::string> &args, int fd, Client &client, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads, std::vector<Reply> &replies)
{
    if (check_args(args, fd, 1, 1) == true)
        return;
    std::vector<std::string> &context = client.get_position();
    if (context[0].empty()) {
        for (const auto &team : teams)
            create_message(rfc_msg[LIST_TEAM].msg, team.uuid, team.name, team.description, fd, false, false, 0, "");
    } else if (!context[0].empty() && context[1].empty()) {
        for (const auto &channel : channels)
            create_message(rfc_msg[LIST_CHANNEL].msg, channel.uuid, channel.name, channel.description, fd, false, false, 0, "");
    } else if (!context[0].empty() && !context[1].empty() && context[2].empty()) {
        for (const auto &thread : threads)
            create_message(rfc_msg[LIST_THREAD].msg, thread.uuid, thread.title, thread.body, fd, true, false, thread.timestamp, thread.user_uuid);
    } else {
        for (const auto &reply : replies)
            create_message(rfc_msg[LIST_REPLY].msg, reply.thread_uuid, "", reply.body, fd, false, true, reply.timestamp, reply.user_uuid);
    }
}


void Server_Command::info(std::vector<std::string> &args, int fd, Client &client, std::vector<Team> &teams, std::vector<Channel> &channels, std::vector<Thread> &threads)
{
    if (check_args(args, fd, 1, 1))
        return;
    std::vector<std::string> &context = client.get_position();
    if (context.size() < 3)
        return;
    if (context[0].empty()) {
        User *user = client.get_user();
        if (user == nullptr) {
            write(fd, (rfc_msg[NOT_LOG].msg + "\r\n").c_str(), rfc_msg[NOT_LOG].msg.size() + 2);
            return;
        }
        std::string msg = rfc_msg[INFO_USER].msg + "|" + user->uuid + "|" + user->name + "|" + (user->status == true ? "1" : "0") + "\r\n";
        write(fd, msg.c_str(), msg.size());
        return;
    }
    else if (!context[0].empty() && context[1].empty()) {
        for (const auto &team : teams) {
            if (team.uuid == context[0]) {
                create_message(rfc_msg[INFO_TEAM].msg, team.uuid, team.name, team.description, fd, false, false, 0, "");
                break;
            }
        }
        return;
    }
    else if (!context[0].empty() && !context[1].empty() && context[2].empty()) {
        for (const auto &channel : channels) {
            if (channel.uuid == context[1]) {
                create_message(rfc_msg[INFO_CHANNEL].msg, channel.uuid, channel.name, channel.description, fd, false, false, 0, "");
                break;
            }
        }
        return;
    } else {
        for (const auto &thread : threads) {
            if (thread.uuid == context[2]) {
                create_message(rfc_msg[INFO_THREAD].msg, thread.uuid, thread.title, thread.body, fd, true, false, thread.timestamp, thread.user_uuid);
                return;
            }
        }
    }
}