/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** Handle_output implementation
*/

#include "Handle_output.hpp"
#include <unordered_map>
#include <functional>
#include <sstream>
#include <string>

extern "C" {
#include "logging_client.h"
}

Handle_output::Handle_output()
{
}

Handle_output::~Handle_output()
{
}

bool Handle_output::find_type(std::string output, std::string type)
{
    return (type == output.substr(4, type.length()));
}

void Handle_output::handle_login(std::string output)
{
    std::stringstream ss(output);
    std::string user_uuid;
    std::string user_name;
    std::getline(ss, user_uuid, '|');
    std::getline(ss, user_name, '|');
    client_event_logged_in(user_uuid.c_str(), user_name.c_str());
}

void Handle_output::handle_logout(std::string output)
{
    std::stringstream ss(output);
    std::string user_uuid;
    std::string user_name;
    std::getline(ss, user_uuid, '|');
    std::getline(ss, user_name, '|');
    client_event_logged_out(user_uuid.c_str(), user_name.c_str());
}

void Handle_output::handle_send(std::string output)
{
    std::stringstream ss(output);
    std::string user_uuid;
    std::string message_body;
    std::getline(ss, user_uuid, '|');
    std::getline(ss, message_body, '|');
    client_event_private_message_received(user_uuid.c_str(), message_body.c_str());
}

void Handle_output::handle_create_reply_body(std::string output)
{
    std::stringstream ss(output);
    std::string team_uuid;
    std::string thread_uuid;
    std::string user_uuid;
    std::string reply_body;
    std::getline(ss, team_uuid, '|');
    std::getline(ss, thread_uuid, '|');
    std::getline(ss, user_uuid, '|');
    std::getline(ss, reply_body, '|');
    client_event_thread_reply_received(team_uuid.c_str(), thread_uuid.c_str(), user_uuid.c_str(), reply_body.c_str());
}

void Handle_output::handle_create_team(std::string output)
{
    std::stringstream ss(output);
    std::string team_uuid;
    std::string team_name;
    std::string team_description;
    std::getline(ss, team_uuid, '|');
    std::getline(ss, team_name, '|');
    std::getline(ss, team_description, '|');
    client_event_team_created(team_uuid.c_str(), team_name.c_str(), team_description.c_str());
}

void Handle_output::handle_create_channel(std::string output)
{
    std::stringstream ss(output);
    std::string channel_uuid;
    std::string channel_name;
    std::string channel_description;
    std::getline(ss, channel_uuid, '|');
    std::getline(ss, channel_name, '|');
    std::getline(ss, channel_description, '|');
    client_event_channel_created(channel_uuid.c_str(), channel_name.c_str(), channel_description.c_str());
}

void Handle_output::handle_create_thread(std::string output)
{
    std::stringstream ss(output);
    std::string thread_uuid;
    std::string user_uuid;
    std::string thread_timestamp;
    std::string thread_title;
    std::string thread_body;
    std::getline(ss, thread_uuid, '|');
    std::getline(ss, user_uuid, '|');
    std::getline(ss, thread_timestamp, '|');
    std::getline(ss, thread_title, '|');
    std::getline(ss, thread_body, '|');
    client_event_thread_created(thread_uuid.c_str(), user_uuid.c_str(), static_cast<time_t>(std::stoll(thread_timestamp)), thread_title.c_str(), thread_body.c_str());
}

void Handle_output::handle_list_users(std::string output)
{
    std::stringstream ss(output);
    std::string line;
    
    while (std::getline(ss, line)) {
        if (line.empty())
            continue;
        std::stringstream line_ss(line);
        std::string user_uuid;
        std::string user_name;
        std::string user_status_str;
        
        std::getline(line_ss, user_uuid, '|');
        std::getline(line_ss, user_name, '|');
        std::getline(line_ss, user_status_str, '|');
        
        int user_status = std::stoi(user_status_str);
        client_print_users(user_uuid.c_str(), user_name.c_str(), user_status);
    }
}

void Handle_output::handle_list_teams(std::string output)
{
    std::stringstream ss(output);
    std::string line;
    
    while (std::getline(ss, line)) {
        if (line.empty())
            continue;
        std::stringstream line_ss(line);
        std::string team_uuid;
        std::string team_name;
        std::string team_description;
        
        std::getline(line_ss, team_uuid, '|');
        std::getline(line_ss, team_name, '|');
        std::getline(line_ss, team_description, '|');
        
        client_print_teams(team_uuid.c_str(), team_name.c_str(), team_description.c_str());
    }
}

void Handle_output::handle_list_channels(std::string output)
{
    std::stringstream ss(output);
    std::string line;
    
    while (std::getline(ss, line)) {
        if (line.empty())
            continue;
        std::stringstream line_ss(line);
        std::string channel_uuid;
        std::string channel_name;
        std::string channel_description;
        
        std::getline(line_ss, channel_uuid, '|');
        std::getline(line_ss, channel_name, '|');
        std::getline(line_ss, channel_description, '|');
        
        client_team_print_channels(channel_uuid.c_str(), channel_name.c_str(), channel_description.c_str());
    }
}

void Handle_output::handle_list_threads(std::string output)
{
    std::stringstream ss(output);
    std::string line;
    
    while (std::getline(ss, line)) {
        if (line.empty())
            continue;
        std::stringstream line_ss(line);
        std::string thread_uuid;
        std::string user_uuid;
        std::string thread_timestamp;
        std::string thread_title;
        std::string thread_body;
        
        std::getline(line_ss, thread_uuid, '|');
        std::getline(line_ss, user_uuid, '|');
        std::getline(line_ss, thread_timestamp, '|');
        std::getline(line_ss, thread_title, '|');
        std::getline(line_ss, thread_body, '|');
        
        client_channel_print_threads(thread_uuid.c_str(), user_uuid.c_str(), static_cast<time_t>(std::stoll(thread_timestamp)), thread_title.c_str(), thread_body.c_str());
    }
}

void Handle_output::handle_list_replies(std::string output)
{
    std::stringstream ss(output);
    std::string line;
    
    while (std::getline(ss, line)) {
        if (line.empty())
            continue;
        std::stringstream line_ss(line);
        std::string thread_uuid;
        std::string user_uuid;
        std::string reply_timestamp;
        std::string reply_body;
        
        std::getline(line_ss, thread_uuid, '|');
        std::getline(line_ss, user_uuid, '|');
        std::getline(line_ss, reply_timestamp, '|');
        std::getline(line_ss, reply_body, '|');
        
        client_thread_print_replies(thread_uuid.c_str(), user_uuid.c_str(), static_cast<time_t>(std::stoll(reply_timestamp)), reply_body.c_str());
    }
}

void Handle_output::handle_list_messages(std::string output)
{
    std::stringstream ss(output);
    std::string line;
    
    while (std::getline(ss, line)) {
        if (line.empty())
            continue;
        std::stringstream line_ss(line);
        std::string sender_uuid;
        std::string message_timestamp;
        std::string message_body;
        
        std::getline(line_ss, sender_uuid, '|');
        std::getline(line_ss, message_timestamp, '|');
        std::getline(line_ss, message_body, '|');
        
        client_private_message_print_messages(sender_uuid.c_str(), static_cast<time_t>(std::stoll(message_timestamp)), message_body.c_str());
    }
}

void Handle_output::handle_info_user(std::string output)
{
    std::stringstream ss(output);
    std::string user_uuid;
    std::string user_name;
    std::string user_status_str;
    
    std::getline(ss, user_uuid, '|');
    std::getline(ss, user_name, '|');
    std::getline(ss, user_status_str, '|');
    
    int user_status = std::stoi(user_status_str);
    client_print_user(user_uuid.c_str(), user_name.c_str(), user_status);
}

void Handle_output::handle_info_team(std::string output)
{
    std::stringstream ss(output);
    std::string team_uuid;
    std::string team_name;
    std::string team_description;
    
    std::getline(ss, team_uuid, '|');
    std::getline(ss, team_name, '|');
    std::getline(ss, team_description, '|');
    
    client_print_team(team_uuid.c_str(), team_name.c_str(), team_description.c_str());
}

void Handle_output::handle_info_channel(std::string output)
{
    std::stringstream ss(output);
    std::string channel_uuid;
    std::string channel_name;
    std::string channel_description;
    
    std::getline(ss, channel_uuid, '|');
    std::getline(ss, channel_name, '|');
    std::getline(ss, channel_description, '|');
    
    client_print_channel(channel_uuid.c_str(), channel_name.c_str(), channel_description.c_str());
}

void Handle_output::handle_info_thread(std::string output)
{
    std::stringstream ss(output);
    std::string thread_uuid;
    std::string user_uuid;
    std::string thread_timestamp;
    std::string thread_title;
    std::string thread_body;
    
    std::getline(ss, thread_uuid, '|');
    std::getline(ss, user_uuid, '|');
    std::getline(ss, thread_timestamp, '|');
    std::getline(ss, thread_title, '|');
    std::getline(ss, thread_body, '|');
    
    client_print_thread(thread_uuid.c_str(), user_uuid.c_str(), static_cast<time_t>(std::stoll(thread_timestamp)), thread_title.c_str(), thread_body.c_str());
}

void Handle_output::handle_subscribe(std::string output)
{
    std::stringstream ss(output);
    std::string user_uuid;
    std::string team_uuid;
    
    std::getline(ss, user_uuid, '|');
    std::getline(ss, team_uuid, '|');
    
    client_print_subscribed(user_uuid.c_str(), team_uuid.c_str());
}

void Handle_output::handle_unsubscribe(std::string output)
{
    std::stringstream ss(output);
    std::string user_uuid;
    std::string team_uuid;
    
    std::getline(ss, user_uuid, '|');
    std::getline(ss, team_uuid, '|');
    
    client_print_unsubscribed(user_uuid.c_str(), team_uuid.c_str());
}

void Handle_output::handle_subscribed_users(std::string output)
{
    handle_list_users(output);
}

void Handle_output::handle_print_team_created(std::string output)
{
    std::stringstream ss(output);
    std::string team_uuid;
    std::string team_name;
    std::string team_description;
    
    std::getline(ss, team_uuid, '|');
    std::getline(ss, team_name, '|');
    std::getline(ss, team_description, '|');
    
    client_print_team_created(team_uuid.c_str(), team_name.c_str(), team_description.c_str());
}

void Handle_output::handle_print_channel_created(std::string output)
{
    std::stringstream ss(output);
    std::string channel_uuid;
    std::string channel_name;
    std::string channel_description;
    
    std::getline(ss, channel_uuid, '|');
    std::getline(ss, channel_name, '|');
    std::getline(ss, channel_description, '|');
    
    client_print_channel_created(channel_uuid.c_str(), channel_name.c_str(), channel_description.c_str());
}

void Handle_output::handle_print_thread_created(std::string output)
{
    std::stringstream ss(output);
    std::string thread_uuid;
    std::string user_uuid;
    std::string thread_timestamp;
    std::string thread_title;
    std::string thread_body;
    
    std::getline(ss, thread_uuid, '|');
    std::getline(ss, user_uuid, '|');
    std::getline(ss, thread_timestamp, '|');
    std::getline(ss, thread_title, '|');
    std::getline(ss, thread_body, '|');
    
    client_print_thread_created(thread_uuid.c_str(), user_uuid.c_str(), static_cast<time_t>(std::stoll(thread_timestamp)), thread_title.c_str(), thread_body.c_str());
}

void Handle_output::handle_print_reply_created(std::string output)
{
    std::stringstream ss(output);
    std::string thread_uuid;
    std::string user_uuid;
    std::string reply_timestamp;
    std::string reply_body;
    
    std::getline(ss, thread_uuid, '|');
    std::getline(ss, user_uuid, '|');
    std::getline(ss, reply_timestamp, '|');
    std::getline(ss, reply_body, '|');
    
    client_print_reply_created(thread_uuid.c_str(), user_uuid.c_str(), static_cast<time_t>(std::stoll(reply_timestamp)), reply_body.c_str());
}

void Handle_output::handle_error_unknown_team(std::string output)
{
    std::stringstream ss(output);
    std::string team_uuid;
    std::getline(ss, team_uuid, '|');
    client_error_unknown_team(team_uuid.c_str());
}

void Handle_output::handle_error_unknown_channel(std::string output)
{
    std::stringstream ss(output);
    std::string channel_uuid;
    std::getline(ss, channel_uuid, '|');
    client_error_unknown_channel(channel_uuid.c_str());
}

void Handle_output::handle_error_unknown_thread(std::string output)
{
    std::stringstream ss(output);
    std::string thread_uuid;
    std::getline(ss, thread_uuid, '|');
    client_error_unknown_thread(thread_uuid.c_str());
}

void Handle_output::handle_error_unknown_user(std::string output)
{
    std::stringstream ss(output);
    std::string user_uuid;
    std::getline(ss, user_uuid, '|');
    client_error_unknown_user(user_uuid.c_str());
}

void Handle_output::handle_error_unauthorized()
{
    client_error_unauthorized();
}

void Handle_output::handle_error_already_exist()
{
    client_error_already_exist();
}

void Handle_output::parse_output(std::string output)
{

    if (!output.empty() && output.back() == '\n')
        output.pop_back();
    if (!output.empty() && output.back() == '\r')
        output.pop_back();

    std::stringstream ss(output);
    std::string header;
    std::string data;
    std::getline(ss, header, '|');
    std::getline(ss, data);
    
    const std::unordered_map<std::string, std::function<void(std::string&)>> commands = 
    {
        {"0:1", [&](std::string& d) { handle_login(d); }},
        {"0:2", [&](std::string& d) { handle_logout(d); }},
        {"0:3", [&](std::string& d) { handle_info_user(d); }},
        {"0:4", [&](std::string& d) { handle_list_users(d); }},
        {"0:5", [&](std::string& d) { handle_send(d); }},
        {"0:6", [&](std::string& d) { handle_list_messages(d); }},
        {"0:8:Team", [&](std::string& d) { handle_create_team(d); handle_print_team_created(d);}},
        {"0:8:Channel", [&](std::string& d) { handle_create_channel(d); handle_print_channel_created(d);}},
        {"0:8:Thread", [&](std::string& d) { handle_create_thread(d); handle_print_thread_created(d);}},
        {"0:8:Reply", [&](std::string& d) { handle_create_reply_body(d); handle_print_reply_created(d);}},
        {"0:11", [&](std::string& d) { handle_subscribe(d); }},
        {"0:12", [&](std::string& d) { handle_unsubscribe(d); }},
        {"0:9:User", [&](std::string& d) { handle_info_user(d); }},
        {"0:9:Team", [&](std::string& d) { handle_info_team(d); }},
        {"0:9:Channel", [&](std::string& d) { handle_info_channel(d); }},
        {"0:9:Thread", [&](std::string& d) { handle_info_thread(d); }},
        {"0:10:Team", [&](std::string& d) { handle_list_teams(d); }},
        {"0:10:Channel", [&](std::string& d) { handle_list_channels(d); }},
        {"0:10:Thread", [&](std::string& d) { handle_list_threads(d); }},
        {"0:10:Reply", [&](std::string& d) { handle_list_replies(d); }},
        {"1:6:Team", [&](std::string& d) { handle_error_unknown_team(d); }},
        {"1:6:Channel", [&](std::string& d) { handle_error_unknown_channel(d); }},
        {"1:6:Thread", [&](std::string& d) { handle_error_unknown_thread(d); }},
        {"1:7", [&](std::string& d) { handle_error_unknown_user(d); }},
        {"1:8", [&](std::string&) { handle_error_already_exist(); }},
        {"2:2", [&](std::string&) { handle_error_unauthorized(); }},
        {"2:5", [&](std::string& d) { handle_subscribed_users(d); }},
    };
    
    for (const auto& [key, func] : commands) {
        if (output.substr(0, key.length()) == key) {
            func(data);
            return;
        }
    }
}