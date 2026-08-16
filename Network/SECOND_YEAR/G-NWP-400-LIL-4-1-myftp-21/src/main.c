/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** main
*/

#include "msg_errors.h"
#include "ftp.h"

void send_msg(int value, ftp_t *ftp_args)
{
    if (ftp_args->poll == NULL)
        return;
    write(ftp_args->poll[ftp_args->pos].fd,
        error_messages[value].msg, strlen(error_messages[value].msg));
    return;
}

static int parse_args(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "--help") == 0) {
        printf("USAGE: ./myftp port path\n");
        printf(" port is the port number ");
        printf("on which the server socket listens\n");
        printf(" path is the path to the ");
        printf("home directory for the Anonymous user\n");
        return 0;
    }
    if (ac != 3)
        return 84;
    for (int i = 0; av[1][i] != '\0'; i++) {
        if (av[1][i] < '0' || av[1][i] > '9') {
            printf("The port is not a number\n");
            return 84;
        }
    }
    return 1;
}

static int init_server(int *socket_server
    , struct sockaddr_in *address_server, char **av)
{
    int activate = 1;

    (*socket_server) = socket(AF_INET, SOCK_STREAM, 0);
    if ((*socket_server) == -1)
        return 84;
    if (setsockopt(*socket_server, SOL_SOCKET, SO_REUSEADDR,
            &activate, sizeof(activate)) == -1)
        return 84;
    (*address_server).sin_family = AF_INET;
    (*address_server).sin_port = htons(atoi(av[1]));
    (*address_server).sin_addr.s_addr = INADDR_ANY;
    if (bind(*socket_server, (struct sockaddr *)address_server
            , sizeof((*address_server))) == -1 ||
        listen((*socket_server), 5000) == -1)
        return 84;
    return 0;
}

int check_path(char **av, ftp_t *ftp_args)
{
    char fix_path[PATH_MAX];
    struct stat sb;

    if (realpath(av[2], fix_path) == NULL)
        return 84;
    if (stat(fix_path, &sb) == -1 || !S_ISDIR(sb.st_mode))
        return 84;
    ftp_args->rpath = strdup(fix_path);
    if (!ftp_args->rpath)
        return 84;
    return 0;
}

int main(int ac, char **av)
{
    int socket_server = -1;
    int status = parse_args(ac, av);
    ftp_t ftp_args = {};
    struct sockaddr_in address_server = {};

    if (status != 1)
        return status;
    if (init_server(&socket_server, &address_server, av) == 84)
        return 84;
    ftp_args.address_server = address_server;
    if (check_path(av, &ftp_args) == 84)
        return 84;
    if (recover_clients(socket_server, &ftp_args) == 84)
        return 84;
    free(ftp_args.rpath);
    close(socket_server);
    return 0;
}
