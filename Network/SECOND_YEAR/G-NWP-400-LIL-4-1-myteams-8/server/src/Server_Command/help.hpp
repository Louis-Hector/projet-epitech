/*
** EPITECH PROJECT,

 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** help
*/

#ifndef HELP_HPP_
#define HELP_HPP_

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#include <vector>

typedef struct {
    std::string name;
    std::string  description;
    std::string body;
} help_msg_t;

static const std::vector<help_msg_t> help_msg =
{
    {
        "help\n",
        "show help\n",
        "/help ?[command]\n"
    },    
    {
        "login\n",
        "set the user_name used by client\n",
        "/login [”user_name”]\n"
    },    
    {
        "logout\n",
        "disconnect the client from the server\n",
        "/logout\n"
    },    
    {
        "users\n",
        "get the list of all users that exist on the domain\n",
        "/users\n"
    },    
    {
        "user\n",
        "get details about the requested user\n",
        "/user [”user_uuid”]\n"
    },    
    {
        "send\n",
        "send a message to specific user\n",
        "/send [”user_uuid”] [”message_body”]\n"
    },    
    {
        "messages\n",
        "list all messages exchanged with the specified user\n",
        "/messages [”user_uuid”]\n"
    },    
    {
        "subscribe\n",
        "subscribe to the events of a team and its sub directories (enable reception of all events from a team)\n",
        "/subscribe [”team_uuid”]\n"
    },    
    {
        "subscribed\n",
        "list all subscribed teams or list all users subscribed to a team\n",
        "/subscribed ?[”team_uuid”]\n"
    },    
    {
        "unsubscribe\n",
        "unsubscribe from a team\n",
        "/unsubscribe [”team_uuid”]\n"
    },    
    {
        "use\n",
        "sets the command context to a team/channel/thread\n",
        "/use ?[”team_uuid”] ?[”channel_uuid”] ?[”thread_uuid”]\n"
    },    
    {
        "create\n",
        "When the context is not defined:\n\tcreate a new team\n"
        "When team_uuid is defined:\n\tcreate a new channel\n"
        "When team_uuid and channel_uuid are defined:\n\tcreate a new thread\n"
        "When team_uuid, channel_uuid and thread_uuid are defined:\n\tcreate a new reply",
        "/create [”team_name”] [”team_description”]\n"
        "/create [”channel_name”] [”channel_description”]\n"
        "/create [”thread_title”] [”thread_message”]\n"
        "/create [”comment_body”]\n"
    },    
    {
        "list\n",

        "When the context is not defined:\n\tlist all existing teams\n"
        "When team_uuid is defined:\n\tlist all existing channels\n"
        "When team_uuid and channel_uuid are defined:\n\tlist all existing threads\n"
        "When team_uuid, channel_uuid and thread_uuid are defined:\n\tlist all existing replies\n",

        "/list"
    },    
    {
        "info\n",

        "When the context is not defined:\n\tdisplay currently logged-in user details\n"
        "When team_uuid is defined\n\tdisplay currently selected team details\n"
        "When team_uuid and channel_uuid are defined\n\tdisplay currently selected channel details\n"
        "When team_uuid, channel_uuid and thread_uuid are defined\n\tdisplay currently selected thread details\n",

        "/info\n"
    }
    
};

#endif /* !HELP_HPP_ */
