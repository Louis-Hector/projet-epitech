/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** miscellaneous_command
*/

#include "ftp.h"

int do_nothing(char *args, ftp_t *ftp_args)
{
    (void)args;
    if (args != NULL) {
        send_msg(ACTION_NOT, ftp_args);
        return 0;
    }
    send_msg(COMMAND_OK, ftp_args);
    return 0;
}
