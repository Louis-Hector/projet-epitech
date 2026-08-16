/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** redirection.c
*/

#include "shell.h"

int check_everything(command_t *commands, env_t **linked_list, shell_t *shell)
{
    if (check_globbins(commands, shell) == 1)
        return shell->return_value;
    if (check_builtins(commands, linked_list, shell) != 2)
        return shell->return_value;
    execute_command(shell, linked_list, commands);
    return shell->return_value;
}

static int change_direction_left(command_t *commands)
{
    int fd = 0;

    if (commands->file == NULL) {
        dprintf(2, "Missing name for redirect.\n");
        return 1;
    }
    fd = open(commands->file, O_RDONLY);
    if (fd == -1)
        return 1;
    if (dup2(fd, STDIN_FILENO) == -1) {
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

static int change_direction_right(command_t *commands)
{
    int fd = 0;

    if (commands->file == NULL) {
        dprintf(2, "Missing name for redirect.\n");
        return 1;
    }
    fd = open(commands->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return 1;
    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

static int change_direction_double(command_t *commands)
{
    int fd = 0;

    if (commands->file == NULL) {
        dprintf(2, "Missing name for redirect.\n");
        return 1;
    }
    fd = open(commands->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        return 1;
    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

static void get_input(int read_write[2], command_t *redi)
{
    char *line = NULL;
    ssize_t bytes_read;
    size_t len = 0;

    while (1) {
        write(1, "? ", 2);
        bytes_read = getline(&line, &len, stdin);
        if (bytes_read == -1)
            break;
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (strcmp(line, redi->file) == 0)
            break;
        line[bytes_read - 1] = '\n';
        write(read_write[1], line, strlen(line));
    }
    free(line);
}

static int handle_double_left_redi(command_t *redi)
{
    int read_write[2] = {-1};

    if (redi->file == NULL) {
        dprintf(2, "Missing name for redirect.\n");
        return 1;
    }
    if (pipe(read_write) == -1)
        return -1;
    get_input(read_write, redi);
    close(read_write[1]);
    if (dup2(read_write[0], STDIN_FILENO) == -1) {
        close(read_write[0]);
        return -1;
    }
    close(read_write[0]);
    return 0;
}

int verif_redirection_left(command_t *commands, env_t **env, shell_t *shell)
{
    int save_stdin = dup(STDIN_FILENO);
    int value_redirec = 0;

    if (commands->redir == L_SIMPLE_REDI) {
        if (change_direction_left(commands) == 1)
            return 1;
        value_redirec = check_everything(commands, env, shell);
        dup2(save_stdin, STDIN_FILENO);
        return value_redirec;
    }
    if (commands->redir == L_DOUBLE_REDI) {
        if (handle_double_left_redi(commands) == 1)
            return 1;
        value_redirec = check_everything(commands, env, shell);
        dup2(save_stdin, STDIN_FILENO);
        return value_redirec;
    }
    return 0;
}

int check_redirection(command_t *commands, env_t **env, shell_t *shell)
{
    int save = dup(STDOUT_FILENO);
    int value_redirec = 0;

    if (commands->redir == R_SIMPLE_REDI) {
        if (change_direction_right(commands) == 1)
            return 1;
        value_redirec = check_everything(commands, env, shell);
        dup2(save, STDOUT_FILENO);
        return value_redirec;
    }
    if (commands->redir == R_DOUBLE_REDI) {
        if (change_direction_double(commands) == 1)
            return 1;
        value_redirec = check_everything(commands, env, shell);
        dup2(save, STDOUT_FILENO);
        return value_redirec;
    }
    return verif_redirection_left(commands, env, shell);
}
