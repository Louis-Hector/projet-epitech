/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** ftp
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <sys/param.h>
#include <sys/wait.h>

#ifndef FTP_H_
    #define FTP_H_

typedef enum {
    FILE_OK,
    COMMAND_OK,
    NEW_CLIENT,
    LESS_CLIENT,
    CLOSE_FILE,
    LOGIN,
    FILE_ACTION_OK,
    NEED_PASS,
    NEED_USER,
    SOCKET_FAIL,
    COMMAND_ERROR,
    MISSING_ARGS,
    NOT_LOGIN,
    ACTION_NOT
} msg_t;

typedef struct {
    //AUTHENTIFICATION
    bool user;
    bool passwd;
    bool good_setp;
    bool session;
    //LES MODES DE TRANSFERTS
    int data_socket;
    struct sockaddr_in addr_connect;

    int mode_transfer;
    //CHEMIN
    char *path;
} client_t;

typedef struct {
    size_t pos;
    size_t max_socket;
    client_t clients[1024];
    struct pollfd *poll;
    struct sockaddr_in address_server;
    char *rpath;
} ftp_t;


typedef struct {
    char *name;
    int (*commands)(char *, ftp_t *);
} commands_t;

//MAIN
void send_msg(int value, ftp_t *ftp_args);

//POLL
int recover_clients(int socket_server, ftp_t *ftp_args);

//CLIENTS
int launch_file_commands(ftp_t *ftp_args, char *command
    , char *args);
int launch_handle_commands(char *buffer, ftp_t *ftp_args);

//LOGIN
int do_user(char *args, ftp_t *ftp_args);
int do_pass(char *args, ftp_t *ftp_args);
int do_cwd(char *args, ftp_t *ftp_args);
int do_cdup(char *args, ftp_t *ftp_args);
int recover_new_path(char *args, ftp_t *ftp, char **fix_path);

//LOGOUT
int do_quit(char *args, ftp_t *ftp_args);

//INFORMATIONAL
int do_help(char *args, ftp_t *ftp_args);

//MISCELLANEOUS
int do_nothing(char *args, ftp_t *ftp_args);

//FILE_COMMANDS
int do_retr(char *arsg, ftp_t *ftp_args);
int do_stor(char *args, ftp_t *ftp_args);
int verif_mode_data(ftp_t *ftp_args, int *data);
void close_file_descriptor(int fd_1, int fd_2, int fd_3, DIR *dir);

//LIST COMMAND PATH
int do_delete(char *args, ftp_t *ftp_args);
int do_pwd(char *args, ftp_t *ftp_args);
int do_list(char *args, ftp_t *ftp_args);

//TRANSFER COMMAND
int do_port(char *args, ftp_t *ftp_args);
int do_pasv(char *arsg, ftp_t *ftp_args);

#endif /* !FTP_H_ */
