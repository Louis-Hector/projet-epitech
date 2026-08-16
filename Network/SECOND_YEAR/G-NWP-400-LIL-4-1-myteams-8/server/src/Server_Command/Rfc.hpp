/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** Rfc
*/

#ifndef RFC_HPP_
#define RFC_HPP_

#include <string>
#include <vector>

typedef struct rfc_msg_s {
    std::string msg;
} rfc_msg_t;

enum RFC_SUCCESS 
{
    COMMAND_VALID,
    LOGIN,
    LOGOUT,
    USER,
    USERS,
    SEND,
    MESSAGES,
    USE,
    CREATE_TEAM,
    CREATE_CHANNEL,
    CREATE_THREAD,
    CREATE_REPLY,
    INFO_USER,
    INFO_TEAM,
    INFO_CHANNEL,
    INFO_THREAD,
    LIST_TEAM,
    LIST_CHANNEL,
    LIST_THREAD,
    LIST_REPLY,
    SUBSCRIBE,
    UNSUBSCRIBE,
};

enum RFC_ERROR
{
    INVALID_ARGS = 22,
    TOO_MANY_ARGS = 23,
    NOT_ENOUGH_ARGS = 24,
    NAME_LENGHT = 25,
    BODY_LENGHT = 26,
    DESCRIPTION_LENGHT = 27,
    USER_ERROR = 28,
    TEAM_ERROR = 29,
    CHANNEL_ERROR = 30,
    THREAD_ERROR = 31,
    UNKNOWN_USER = 32,
    ALREADY_SUB  = 33
};

enum RFC_INFOS 
{
    NEW_CONNECTION = 34,
    NEW_DECONNECTION = 35,
    ALREADY_LOG = 36,
    NOT_LOG = 37,
    NOT_LOCATION = 38,
    NOTIFY_OTHER = 39,
    LIST_SUB = 40,
    NEED_QUOTE = 41,
};

const std::vector<rfc_msg_t> rfc_msg = 
{
    {"0:0:Command successfully completed"},
    {"0:1:Logged in with success"},
    {"0:2:The user is logging out"},
    {"0:3: Details about the requested user"},
    {"0:4:All the users"},
    {"0:5:Message send"},
    {"0:6:Messages exchanged"},
    {"0:7:Successful movement, change of position"},
    {"0:8:Team create"},
    {"0:8:Channel create"},
    {"0:8:Thread create"},
    {"0:8:Reply create"},
    {"0:9:User info"},
    {"0:9:Team info"},
    {"0:9:Channel info"},
    {"0:9:Thread info"},
    {"0:10:Team list"},
    {"0:10:Channel list"},
    {"0:10:Thread list"},
    {"0:10:Reply list"},
    {"0:11:Subscribe to the events of a team"},
    {"0:12:Unsubscribe from a team"},
    {"1:0:Args error, invalid command"},
    {"1:1:Args error, too many arguments"},
    {"1:2:Args error, not enough arguments"},
    {"1:3:Args error, the name of the user is too long not logged in"},
    {"1:4:Args error, the message_body is too long"},
    {"1:5:Args error, the description is too long"},
    {"1:6:User error action"},
    {"1:6:Team error action"},
    {"1:6:Channel error action"},
    {"1:6:Thread error action"},
    {"1:7:Uknown user"},
    {"1:8:User action and the resource already exist"},
    {"2:0:A user has just logged in"},
    {"2:7:A user has just logged off"},
    {"2:1:The user is already logged in; please log in using another account"},
    {"2:2:The user is not logged in (available command /help or /login)"},
    {"2:3:This location does not exist; relocation is not possible"},
    {"2:4:New user subscribe"},
    {"2:5:Subscribe list"},
    {"2:6:Args Need quote to be valid"}
};

#endif /* !RFC_HPP_ */
