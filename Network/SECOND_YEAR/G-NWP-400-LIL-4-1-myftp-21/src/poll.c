/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** actions
*/

#include "ftp.h"

int remove_client(struct pollfd *tab_sockets
    , ftp_t *ftp_args, int *i, int *max_socket)
{
    int last_client = *max_socket - 1;

    if (tab_sockets[(*i)].revents & (POLLERR | POLLHUP | POLLNVAL)) {
        close(tab_sockets[(*i)].fd);
        if (ftp_args->clients[(*i)].path != NULL)
            free(ftp_args->clients[(*i)].path);
        if (*i != last_client) {
            tab_sockets[(*i)] = tab_sockets[last_client];
            ftp_args->clients[(*i)] = ftp_args->clients[last_client];
        }
        tab_sockets[last_client].fd = -1;
        (*max_socket) -= 1;
        (*i) -= 1;
        return 1;
    }
    return 0;
}

void check_actions_client(struct pollfd *tab_sockets, int *i
    , int *max_socket, ftp_t *ftp_args)
{
    char buffer[1024] = {};
    ssize_t bits = 0;

    if (remove_client(tab_sockets, ftp_args, i, max_socket) == 1)
        return;
    if (tab_sockets[(*i)].revents & (POLLIN)) {
        bits = read(tab_sockets[(*i)].fd, buffer, sizeof(buffer) - 1);
        if (bits == 0) {
            remove_client(tab_sockets, ftp_args, i, max_socket);
            return;
        }
        if (bits == -1)
            return;
        buffer[bits] = '\0';
        launch_handle_commands(buffer, ftp_args);
        *i = ftp_args->pos;
        *max_socket = ftp_args->max_socket;
    }
}

int browse_clients(struct pollfd *tab_sockets
    , int *max_socket, ftp_t *ftp_args)
{
    for (int i = 1; i < *max_socket; i++) {
        ftp_args->pos = i;
        ftp_args->poll = tab_sockets;
        ftp_args->max_socket = *max_socket;
        check_actions_client(tab_sockets
            , &i, max_socket, ftp_args);
    }
    return 0;
}

static int init_client(struct pollfd *tab_sockets
    , int *max_socket, ftp_t *ftp_args)
{
    tab_sockets[*max_socket].events = POLLIN;
    ftp_args->clients[*max_socket].user = false;
    ftp_args->clients[*max_socket].passwd = false;
    ftp_args->clients[*max_socket].session = false;
    ftp_args->clients[*max_socket].data_socket = -1;
    ftp_args->clients[*max_socket].path = strdup(ftp_args->rpath);
    if (ftp_args->clients[*max_socket].path == NULL)
        return 84;
    return 0;
}

bool check_new_client(int socket_server, int *max_socket
    , struct pollfd *tab_sockets, ftp_t *ftp_args)
{
    socklen_t size_socket = 0;
    struct sockaddr_in address_client = {};
    const char *msg = "220 Service ready for new user.\r\n";

    if (tab_sockets[0].revents & POLLIN) {
        if (*max_socket >= 5000)
            return 0;
        size_socket = sizeof(address_client);
        tab_sockets[*max_socket].fd = accept(socket_server
            , (struct sockaddr *)&address_client, &size_socket);
        if (tab_sockets[*max_socket].fd == -1)
            return 0;
        if (init_client(tab_sockets, max_socket, ftp_args) == 84)
            return 84;
        write(tab_sockets[*max_socket].fd, msg, strlen(msg));
        *max_socket += 1;
    }
    return 1;
}

int recover_clients(int socket_server, ftp_t *ftp_args)
{
    struct pollfd tab_client[5000] = {};
    int max_socket = 1;
    int status = 0;

    tab_client[0].fd = socket_server;
    tab_client[0].events = POLLIN;
    ftp_args->pos = 1;
    while (1) {
        poll(tab_client, max_socket, -1);
        status = check_new_client(socket_server, &max_socket
            , tab_client, ftp_args);
        if (status == 84)
            return 84;
        if (status == 0)
            continue;
        if (browse_clients(tab_client, &max_socket, ftp_args) == 84)
            return 84;
    }
}
