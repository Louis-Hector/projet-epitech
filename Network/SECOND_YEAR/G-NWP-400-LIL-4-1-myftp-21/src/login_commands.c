/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** login_commands
*/

#include "ftp.h"

int do_user(char *args, ftp_t *ftp_args)
{
    client_t *client = &ftp_args->clients[ftp_args->pos];

    client->session = false;
    client->user = false;
    client->good_setp = true;
    if (args == NULL) {
        send_msg(MISSING_ARGS, ftp_args);
        return 1;
    }
    if (strcmp(args, "Anonymous") == 0 && client->passwd == false)
        client->user = true;
    send_msg(NEED_PASS, ftp_args);
    return 0;
}

int do_pass(char *args, ftp_t *ftp_args)
{
    client_t *client = &ftp_args->clients[ftp_args->pos];

    client->session = false;
    client->passwd = false;
    if (args == NULL && client->user == true && client->good_setp == true) {
        client->passwd = true;
        send_msg(LOGIN, ftp_args);
    }
    if (client->good_setp == false) {
        send_msg(NEED_USER, ftp_args);
        return 0;
    }
    client->good_setp = false;
    if (client->user == true && client->passwd == true) {
        client->session = true;
        return 0;
    }
    send_msg(NOT_LOGIN, ftp_args);
    return 0;
}

int recover_new_path(char *args, ftp_t *ftp, char **fix_path)
{
    int size = strlen(ftp->clients[ftp->pos].path) + strlen(args) + 2;
    char *new_path = NULL;

    new_path = malloc(sizeof(char) * size);
    if (new_path == NULL)
        return 84;
    snprintf(new_path, size, "%s/%s", ftp->clients[ftp->pos].path, args);
    *fix_path = malloc(sizeof(char) * strlen(new_path) + 1);
    if (*fix_path == NULL) {
        free(new_path);
        return 84;
    }
    if (realpath(new_path, *fix_path) == NULL) {
        free(*fix_path);
        free(new_path);
        send_msg(ACTION_NOT, ftp);
        return 1;
    }
    free(new_path);
    return 0;
}

static int affect_fix_path(ftp_t *ftp_args, char *fix_path, int mode)
{
    struct stat sb;

    if (stat(fix_path, &sb) == -1 || !S_ISDIR(sb.st_mode)) {
        send_msg(ACTION_NOT, ftp_args);
        free(fix_path);
        return 0;
    }
    if (ftp_args->clients[ftp_args->pos].path != NULL)
        free(ftp_args->clients[ftp_args->pos].path);
    ftp_args->clients[ftp_args->pos].path = strdup(fix_path);
    if (ftp_args->clients[ftp_args->pos].path == NULL) {
        free(fix_path);
        return 84;
    }
    free(fix_path);
    send_msg(mode, ftp_args);
    return 0;
}

int do_cwd(char *args, ftp_t *ftp_args)
{
    char *fix_path = NULL;
    int status = 0;

    if (args == NULL) {
        send_msg(MISSING_ARGS, ftp_args);
        return 0;
    }
    status = recover_new_path(args, ftp_args, &fix_path);
    if (status != 0)
        return status;
    if (strncmp(ftp_args->rpath, fix_path, strlen(ftp_args->rpath)) != 0) {
        send_msg(ACTION_NOT, ftp_args);
        free(fix_path);
        return 0;
    }
    return affect_fix_path(ftp_args, fix_path, FILE_ACTION_OK);
}

int do_cdup(char *args, ftp_t *ftp_args)
{
    char *fix_path = NULL;
    int status = 0;

    if (args != NULL) {
        send_msg(MISSING_ARGS, ftp_args);
        return 1;
    }
    status = recover_new_path("../", ftp_args, &fix_path);
    if (status != 0)
        return status;
    if (strncmp(ftp_args->rpath, fix_path, strlen(ftp_args->rpath)) != 0) {
        send_msg(ACTION_NOT, ftp_args);
        free(fix_path);
        return 0;
    }
    return affect_fix_path(ftp_args, fix_path, COMMAND_OK);
}
