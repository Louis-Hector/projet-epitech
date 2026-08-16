/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** informational_command
*/

#include "ftp.h"
#include "help.h"

bool search_commands(char *args, int *i, ftp_t *ftp_args)
{
    char *list_command[14] = {"USER", "PASS", "CWD", "CDUP", "QUIT"
        , "DELE", "PWD", "PASV", "PORT", "HELP"
        , "NOOP", "RETR", "STOR", "LIST"};
    bool command_exist = false;

    for (*i = 0; *i < 14; *i += 1) {
        if (strcmp(args, list_command[*i]) == 0) {
            command_exist = true;
            break;
        }
    }
    if (command_exist == false) {
        send_msg(MISSING_ARGS, ftp_args);
        return false;
    }
    return true;
}

int do_help(char *args, ftp_t *ftp_args)
{
    const char *msg = "USER PASS CWD CDUP QUIT DELE PWD "
        "PASV PORT HELP NOOP RETR STOR LIST\r\n";
    int i = 0;

    if (args == NULL) {
        write(ftp_args->poll[ftp_args->pos].fd, "214 Help message. ", 19);
        write(ftp_args->poll[ftp_args->pos].fd, msg, strlen(msg));
        return 0;
    }
    if (search_commands(args, &i, ftp_args) == false)
        return 0;
    write(ftp_args->poll[ftp_args->pos].fd
        , "214 Help message. ", 19);
    write(ftp_args->poll[ftp_args->pos].fd
        , help[i].msg, strlen(help[i].msg));
    return 0;
}
