/*
** EPITECH PROJECT, 2026
** myteams
** File description:
** Handle_output
*/
#ifndef HANDLE_OUTPUT_HPP_
#define HANDLE_OUTPUT_HPP_

#include <iostream>
#include <sstream>
#include <string>

class Handle_output {
public:
    Handle_output();
    ~Handle_output();
    void parse_output(std::string output);

protected:
private:
    bool find_type(std::string output, std::string type);
    void handle_login(std::string output);
    void handle_logout(std::string output);
    void handle_send(std::string output);
    void handle_create_reply_body(std::string output);
    void handle_create_team(std::string output);
    void handle_create_channel(std::string output);
    void handle_create_thread(std::string output);
    void handle_list_users(std::string output);
    void handle_list_teams(std::string output);
    void handle_list_channels(std::string output);
    void handle_list_threads(std::string output);
    void handle_list_replies(std::string output);
    void handle_list_messages(std::string output);
    void handle_info_user(std::string output);
    void handle_info_team(std::string output);
    void handle_info_channel(std::string output);
    void handle_info_thread(std::string output);
    void handle_subscribe(std::string output);
    void handle_unsubscribe(std::string output);
    void handle_subscribed_users(std::string output);
    void handle_print_team_created(std::string output);
    void handle_print_channel_created(std::string output);
    void handle_print_thread_created(std::string output);
    void handle_print_reply_created(std::string output);
    void handle_error_unknown_team(std::string output);
    void handle_error_unknown_channel(std::string output);
    void handle_error_unknown_thread(std::string output);
    void handle_error_unknown_user(std::string output);
    void handle_error_unauthorized();
    void handle_error_already_exist();
};

#endif /* !HANDLE_OUTPUT_HPP_ */