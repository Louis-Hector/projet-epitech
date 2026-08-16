/*
** EPITECH PROJECT, 2025
** check_redirection.c
** File description:
** verif redirection
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include <signal.h>
#include <string.h>
#include "mylinkedlist.h"
#include <fcntl.h>

int change_direction_right(char **tab, int i)
{
    int fd = 0;

    if (tab[i + 1] == NULL) {
        mini_printf("Missing name for redirect.\n");
        return 1;
    }
    fd = open(tab[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return 1;
    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        return 1;
    }
    close(fd);
    tab[i] = NULL;
    return 0;
}

int change_direction_left(char **tab, int i)
{
    int fd = 0;

    if (tab[i + 1] == NULL) {
        mini_printf("Missing name for redirect.\n");
        return 1;
    }
    fd = open(tab[i + 1], O_RDONLY);
    if (fd == -1)
        return 1;
    if (dup2(fd, STDIN_FILENO) == -1) {
        close(fd);
        return 1;
    }
    close(fd);
    tab[i] = NULL;
    return 0;
}

static int change_direction_double(char **tab, int i)
{
    int fd = 0;

    if (tab[i + 1] == NULL) {
        mini_printf("Missing name for redirect.\n");
        return 1;
    }
    fd = open(tab[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        return 1;
    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        return 1;
    }
    close(fd);
    tab[i] = NULL;
    return 0;
}

void check_everything(char **tab, char **env
    , linked_list_t **linked_list, stock_str_t *val)
{
    if (my_strcmp(tab[0], "env") == 0)
        make_env(linked_list, tab);
    if (my_strcmp(tab[0], "cd") == 0)
        change_directory(tab, val->env);
    if (my_strcmp(tab[0], "setenv") == 0)
        make_setenv(linked_list, tab);
    if (my_strcmp(tab[0], "unsetenv") == 0)
        make_unsetenv(linked_list, tab);
    val->path = getpath(tab, val->env);
    if (val->path != NULL)
        use_fork(val->path, tab, linked_list);
    else
        mini_printf("%s: Command not found.\n", tab[0]);
}

static void return_to_stdout(stock_str_t *val
    , linked_list_t **linked_list, int save, char **tab)
{
    check_everything(tab, val->env, linked_list, val);
    dup2(save, STDOUT_FILENO);
}

int verif_double_and_pipe(char **tab, int i
    , linked_list_t **linked_list, stock_str_t *val)
{
    int save = dup(STDOUT_FILENO);

    if (my_strcmp(tab[i], "|") == 0) {
        if (affect_pipe(tab, i, linked_list, val) == 1)
            return 1;
        return 0;
    }
    if (my_strcmp(tab[i], ">>") == 0) {
        if (change_direction_double(tab, i) == 1)
            return 1;
        return_to_stdout(val, linked_list, save, tab);
        return 0;
    }
    return -1;
}

static int verif_direct(stock_str_t *val
    , linked_list_t **linked_list, int i, char **tab)
{
    int save = dup(STDOUT_FILENO);
    int stat = 0;

    stat = verif_double_and_pipe(tab, i, linked_list, val);
    if (stat == 0 || stat == 1)
        return stat;
    if (my_strcmp(tab[i], ">") == 0) {
        if (change_direction_right(tab, i) == 1)
            return 1;
        return_to_stdout(val, linked_list, save, tab);
        return 0;
    }
    if (my_strcmp(tab[i], "<") == 0) {
        if (change_direction_left(tab, i) == 1)
            return 1;
        check_everything(tab, val->env, linked_list, val);
        return 0;
    }
    return -1;
}

int handle_redirections(char **tab, char **env
    , linked_list_t **linked_list, stock_str_t *val)
{
    int stat = 0;

    for (int i = 0; tab[i] != NULL; i++) {
        stat = verif_direct(val, linked_list, i, tab);
        if (stat == 1)
            return 1;
        if (stat == 0)
            return 0;
    }
    return -1;
}
