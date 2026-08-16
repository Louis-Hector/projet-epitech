/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** logout_commands
*/

#include "ftp.h"

int do_quit(char *args, ftp_t *ftp_args)
{
    (void)args;
    send_msg(LESS_CLIENT, ftp_args);
    close(ftp_args->poll[ftp_args->pos].fd);
    ftp_args->poll[ftp_args->pos] = ftp_args->poll[ftp_args->max_socket - 1];
    if (ftp_args->clients[ftp_args->pos].path != NULL)
        free(ftp_args->clients[ftp_args->pos].path);
    ftp_args->clients[ftp_args->pos]
    = ftp_args->clients[ftp_args->max_socket - 1];
    ftp_args->max_socket -= 1;
    ftp_args->pos -= 1;
    return 0;
}
