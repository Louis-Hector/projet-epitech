/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** file_commands
*/

#include "ftp.h"

void close_file_descriptor(int fd_1, int fd_2, int fd_3, DIR *dir)
{
    if (fd_1 != -1)
        close(fd_1);
    if (fd_2 != -1)
        close(fd_2);
    if (fd_3 != -1)
        close(fd_3);
    if (dir != NULL)
        closedir(dir);
    return;
}

int verif_mode_data(ftp_t *ftp_args, int *data)
{
    int *data_socket = &ftp_args->clients[ftp_args->pos].data_socket;
    struct sockaddr_in ad = ftp_args->clients[ftp_args->pos].addr_connect;

    if (ftp_args->clients[ftp_args->pos].mode_transfer == 1) {
        *data = socket(AF_INET, SOCK_STREAM, 0);
        if (*data == -1 || connect(*data, (struct sockaddr *)
                &ad, sizeof(ad)) == -1) {
            send_msg(SOCKET_FAIL, ftp_args);
            return 1;
        }
    } else {
        *data = accept(*data_socket, NULL, NULL);
        if (*data == -1) {
            send_msg(SOCKET_FAIL, ftp_args);
            return 1;
        }
    }
    return 0;
}

static int recover_file(ftp_t *ftp_args, int data, int file)
{
    pid_t pid = fork();
    char buffer[1024] = {};
    int bits = 0;

    if (pid == -1) {
        send_msg(ACTION_NOT, ftp_args);
        close_file_descriptor(data, file, -1, NULL);
        return 1;
    }
    if (pid == 0) {
        bits = read(file, buffer, sizeof(buffer));
        while (bits > 0) {
            write(data, buffer, bits);
            bits = read(file, buffer, sizeof(buffer));
        }
        exit(0);
    }
    waitpid(pid, NULL, 0);
    return 0;
}

int is_a_file(ftp_t *ftp_args, char *args, int *file)
{
    int status = 0;
    char *fix_path = NULL;
    struct stat sb;

    if (args == NULL) {
        send_msg(ACTION_NOT, ftp_args);
        return 1;
    }
    status = recover_new_path(args, ftp_args, &fix_path);
    if (status != 0)
        return 1;
    *file = open(fix_path, O_RDONLY);
    free(fix_path);
    if (*file == -1 || fstat(*file, &sb) == -1 || S_ISDIR(sb.st_mode)) {
        send_msg(ACTION_NOT, ftp_args);
        return 1;
    }
    return 0;
}

int do_retr(char *args, ftp_t *ftp_args)
{
    int *data_socket = &ftp_args->clients[ftp_args->pos].data_socket;
    int file = -1;
    int data = -1;

    if (*data_socket == -1) {
        send_msg(SOCKET_FAIL, ftp_args);
        return 0;
    }
    if (is_a_file(ftp_args, args, &file) == 1)
        return 0;
    send_msg(FILE_OK, ftp_args);
    if (verif_mode_data(ftp_args, &data) == 1
        || recover_file(ftp_args, data, file) == 1)
        return 0;
    close_file_descriptor(file, data, *data_socket, NULL);
    send_msg(CLOSE_FILE, ftp_args);
    *data_socket = -1;
    return 0;
}

static int adapt_path_list(char *args, char **fix_path, char *path)
{
    int size = 0;

    if (args[0] == '/')
        size = strlen(args) + 1;
    else
        size = strlen(path) + strlen(args) + 2;
    *fix_path = malloc(sizeof(char) * size);
    if (*fix_path == NULL)
        return 84;
    if (args[0] == '/')
        snprintf(*fix_path, size, "%s", args);
    else
        snprintf(*fix_path, size, "%s/%s", path, args);
    return 0;
}

static int create_file(char *args, ftp_t *ftp_args
    , int *file)
{
    struct stat sb;
    char *fix_path = NULL;
    char *path = ftp_args->clients[ftp_args->pos].path;

    if (args == NULL) {
        send_msg(ACTION_NOT, ftp_args);
        return 1;
    }
    if (adapt_path_list(args, &fix_path, path) == 84)
        return 84;
    *file = open(fix_path, O_CREAT | O_WRONLY | O_TRUNC, 0664);
    free(fix_path);
    if (*file == -1 || fstat(*file, &sb) == -1) {
        send_msg(ACTION_NOT, ftp_args);
        return 1;
    }
    return 0;
}

static int write_file(ftp_t *ftp_args, int file, int data)
{
    int bits = 0;
    char buffer[1024] = {};
    pid_t pid = fork();

    if (pid < 0) {
        send_msg(ACTION_NOT, ftp_args);
        close_file_descriptor(data, -1, file, NULL);
        return 1;
    }
    if (pid == 0) {
        bits = read(data, buffer, sizeof(buffer));
        while (bits > 0) {
            write(file, buffer, bits);
            bits = read(data, buffer, sizeof(buffer));
        }
        exit(0);
    }
    waitpid(pid, NULL, 0);
    send_msg(CLOSE_FILE, ftp_args);
    return 0;
}

int do_stor(char *args, ftp_t *ftp_args)
{
    int *data_socket = &ftp_args->clients[ftp_args->pos].data_socket;
    int status = 0;
    int file = -1;
    int data = -1;

    if (*data_socket == -1) {
        send_msg(SOCKET_FAIL, ftp_args);
        return 0;
    }
    status = create_file(args, ftp_args, &file);
    if (status != 0)
        return status;
    send_msg(FILE_OK, ftp_args);
    if (verif_mode_data(ftp_args, &data) == 1 ||
        write_file(ftp_args, file, data) == 1)
        return 0;
    close_file_descriptor(data, *data_socket, file, NULL);
    *data_socket = -1;
    return 0;
}
