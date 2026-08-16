/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** help
*/

#ifndef HELP_H_
    #define HELP_H_

typedef struct {
    const char *msg;
} help_t;

static const help_t help[] = {
    {"USER <SP> <username> <CRLF>   : Specify user for authentication\r\n"},
    {"PASS <SP> <password> <CRLF> : Specify password for authentication\r\n"},
    {"CWD  <SP> <pathname> <CRLF> : Change working directory\r\n"},
    {"CDUP <CRLF>         : Change working directory to parent directory\r\n"},
    {"QUIT <CRLF>                   : Disconnection\r\n"},
    {"DELE <SP> <pathname> <CRLF>   : Delete file on the server\r\n"},
    {"PWD  <CRLF>          : Print working directory\r\n"},
    {"PASV <CRLF>          : Enable passive mode for data transfer\r\n"},
    {"PORT <SP> <host-port> <CRLF>: Enable active mode for data transfer\r\n"},
    {"HELP [<SP> <string>] <CRLF>   : List available commands\r\n"},
    {"NOOP <CRLF>          : Do nothing\r\n"},
    {"RETR <SP> <pathname> <CRLF> : Download file from server to client\r\n"},
    {"STOR <SP> <pathname> <CRLF>   : Upload file from client to server\r\n"},
    {"LIST [<SP> <pathname>] <CRLF> "},
    {": List files in the current working directory\r\n"}
};

#endif /* !HELP_H_ */
