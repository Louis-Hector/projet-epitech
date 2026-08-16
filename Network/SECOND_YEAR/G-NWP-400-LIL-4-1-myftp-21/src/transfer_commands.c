/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** transfer_commands
*/

#include "ftp.h"

static void send_passive_mode(int tab_ip[4], int *data_socket
    , struct sockaddr_in *da_ad, ftp_t *ftp_args)
{
    int port_data = -1;
    char new_address[500] = {};
    socklen_t len = 0;
    struct sockaddr_in cl_ad = {};

    len = sizeof(cl_ad);
    if (getsockname(ftp_args->poll[ftp_args->pos].fd,
            (struct sockaddr *)&cl_ad, &len) == -1)
        return;
    sscanf(inet_ntoa((cl_ad.sin_addr))
        , "%d.%d.%d.%d", &tab_ip[0], &tab_ip[1], &tab_ip[2], &tab_ip[3]);
    len = (sizeof(*da_ad));
    if (getsockname((*data_socket), (struct sockaddr *)da_ad, &len) == -1)
        return;
    port_data = ntohs((*da_ad).sin_port);
    snprintf(new_address, sizeof(new_address),
        "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n"
        , tab_ip[0], tab_ip[1], tab_ip[2], tab_ip[3],
        port_data / 256, port_data % 256);
    write(ftp_args->poll[ftp_args->pos].fd, new_address, strlen(new_address));
}

static int verif_args_pasv(int data_socket, ftp_t *ftp_args, char *args)
{
    if (args != NULL) {
        send_msg(ACTION_NOT, ftp_args);
        return 1;
    }
    if (data_socket == -1) {
        send_msg(SOCKET_FAIL, ftp_args);
        return 1;
    }
    return 0;
}

int do_pasv(char *args, ftp_t *ftp_args)
{
    struct sockaddr_in data_address = {};
    int tab_ip[4] = {0, 0, 0, 0};
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (verif_args_pasv(data_socket, ftp_args, args) == 1)
        return 0;
    data_address.sin_family = ftp_args->address_server.sin_family;
    data_address.sin_addr.s_addr = htonl(INADDR_ANY);
    data_address.sin_port = htons(0);
    if (bind(data_socket, (struct sockaddr *)&data_address
            , sizeof(data_address)) == -1
        || listen(data_socket, 1) == -1)
        return 0;
    send_passive_mode(tab_ip, &data_socket, &data_address, ftp_args);
    ftp_args->clients[ftp_args->pos].data_socket = data_socket;
    ftp_args->clients[ftp_args->pos].mode_transfer = 0;
    return 0;
}

static int verif_data_socket(struct sockaddr_in *data_address, ftp_t *ftp_args)
{
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (data_socket == -1) {
        send_msg(SOCKET_FAIL, ftp_args);
        return 1;
    }
    ftp_args->clients[ftp_args->pos].data_socket = data_socket;
    ftp_args->clients[ftp_args->pos].addr_connect = *data_address;
    ftp_args->clients[ftp_args->pos].mode_transfer = 1;
    return 0;
}

int do_port(char *args, ftp_t *ftp_args)
{
    int ip[4] = {0, 0, 0, 0};
    int port[2] = {0, 0};
    struct sockaddr_in data_address = {};

    if (args == NULL) {
        send_msg(MISSING_ARGS, ftp_args);
        return 0;
    }
    sscanf(args, "%d,%d,%d,%d,%d,%d", &ip[0], &ip[1]
        , &ip[2], &ip[3], &port[0], &port[1]);
    data_address.sin_family = AF_INET;
    data_address.sin_port = htons(port[0] * 256 + port[1]);
    data_address.sin_addr.s_addr = htonl((ip[0] << 24)
        | (ip[1] << 16) | (ip[2] << 8) | (ip[3]));
    if (verif_data_socket(&data_address, ftp_args) == 1)
        return 0;
    send_msg(COMMAND_OK, ftp_args);
    return 0;
}
