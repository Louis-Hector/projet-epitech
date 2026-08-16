/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** list_command
*/

#include "ftp.h"


int do_delete(char *args, ftp_t *ftp_args)
{
    int value = 0;
    char *fix_path = NULL;
    int status = 0;

    if (args == NULL) {
        send_msg(ACTION_NOT, ftp_args);
        return 0;
    }
    status = recover_new_path(args, ftp_args, &fix_path);
    if (status != 0)
        return status;
    value = remove(fix_path);
    if (value != 0) {
        send_msg(ACTION_NOT, ftp_args);
        return 0;
    }
    send_msg(FILE_ACTION_OK, ftp_args);
    free(fix_path);
    return 0;
}

int do_pwd(char *args, ftp_t *ftp_args)
{
    if (args != NULL) {
        send_msg(ACTION_NOT, ftp_args);
        return 0;
    }
    if (ftp_args->clients[ftp_args->pos].path != NULL) {
        write(ftp_args->poll[ftp_args->pos].fd, "257 \"", 5);
        write(ftp_args->poll[ftp_args->pos].fd
            , ftp_args->clients[ftp_args->pos].path
            , strlen(ftp_args->clients[ftp_args->pos].path));
        write(ftp_args->poll[ftp_args->pos].fd, "\" created.\r\n", 13);
        return 0;
    }
    send_msg(ACTION_NOT, ftp_args);
    return 0;
}

int read_directory(int data, DIR *dir, ftp_t *ftp_args)
{
    struct dirent *file;
    pid_t pid = fork();

    if (pid < 0) {
        send_msg(ACTION_NOT, ftp_args);
        close_file_descriptor(data, -1, -1, dir);
        return 1;
    }
    if (pid == 0) {
        file = readdir(dir);
        while (file != NULL) {
            write(data, file->d_name, strlen(file->d_name));
            write(data, "\r\n", 2);
            file = readdir(dir);
        }
        exit(0);
    }
    waitpid(pid, NULL, 0);
    return 0;
}

int recover_directory(ftp_t *ftp_args, DIR **dir, char *args)
{
    char *fix_path = NULL;
    int status = 0;

    if (args == NULL)
        *dir = opendir(ftp_args->clients[ftp_args->pos].path);
    else {
        status = recover_new_path(args, ftp_args, &fix_path);
        if (status != 0)
            return status;
        *dir = opendir(fix_path);
        if (*dir == NULL || strncmp(ftp_args->rpath, fix_path
                , strlen(ftp_args->rpath)) != 0) {
            free(fix_path);
            send_msg(ACTION_NOT, ftp_args);
            return 1;
        }
        free(fix_path);
    }
    return 0;
}

int do_list(char *args, ftp_t *ftp_args)
{
    DIR *dir = NULL;
    int *data_socket = &ftp_args->clients[ftp_args->pos].data_socket;
    int data = -1;
    int status = 0;

    if (*data_socket == -1) {
        send_msg(SOCKET_FAIL, ftp_args);
        return 0;
    }
    status = recover_directory(ftp_args, &dir, args);
    if (status != 0)
        return status;
    send_msg(FILE_OK, ftp_args);
    if (verif_mode_data(ftp_args, &data) == 1
        || read_directory(data, dir, ftp_args) == 1)
        return 0;
    close_file_descriptor(data, *data_socket, -1, dir);
    send_msg(CLOSE_FILE, ftp_args);
    *data_socket = -1;
    return 0;
}
