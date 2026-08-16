/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** client_actions
*/


#include "ftp.h"
#include "commands.h"

static void is_commands(int *valid_command, char *command, ftp_t *ftp_args)
{
    const char *liste_command[14] = {"HELP", "QUIT", "USER"
        , "PASS", "NOOP", "RETR", "LIST", "PASV"
        , "CWD", "CDUP", "DELE", "PWD", "PORT", "STOR"};

    for (int i = 0; i < 14; i++)
        if (strcmp(liste_command[i], command) == 0)
            (*valid_command) = 1;
    if ((*valid_command) == 0) {
        send_msg(COMMAND_ERROR, ftp_args);
        return;
    }
    return;
}

int launch_file_commands(ftp_t *ftp_args, char *command
    , char *args)
{
    if (ftp_args->clients[ftp_args->pos].session == false) {
        send_msg(NOT_LOGIN, ftp_args);
        return 0;
    }
    for (int i = 5; i < 14; i++)
        if (strcmp(command, commands[i].name) == 0)
            return commands[i].commands(args, ftp_args);
    send_msg(COMMAND_ERROR, ftp_args);
    return 0;
}

int launch_handle_commands(char *buffer, ftp_t *ftp_args)
{
    char *command = strtok(buffer, " \r\n");
    char *args = strtok(NULL, " \r\n");
    int valid_command = 0;

    if (command == NULL || strlen(command) == 0) {
        send_msg(COMMAND_ERROR, ftp_args);
        return 0;
    }
    is_commands(&valid_command, command, ftp_args);
    if (valid_command == 0)
        return 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(command, commands[i].name) == 0)
            return commands[i].commands(args, ftp_args);
    }
    return launch_file_commands(ftp_args, command, args);
}
