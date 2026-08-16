/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** create a minishell
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

void free_tab_and_path(char **tab, char *path)
{
    if (path != NULL)
        free(path);
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

static int recup_status(char **tab, stock_str_t *val
    , linked_list_t **linked_list)
{
    if (tab[0] == NULL) {
        write(1, "$> ", 3);
        return 0;
    }
    if (my_strcmp(tab[0], "exit") == 0) {
        free_tab_and_path(tab, val->path);
        free_linked_list(linked_list);
        return 3;
    }
    return 1;
}

static int write_free(char **tab, stock_str_t *val)
{
    write(1, "$> ", 3);
    free_tab_and_path(tab, val->path);
    return 0;
}

static void check_fork(char **tab, linked_list_t **linked_list
    , stock_str_t *val, int *last_status)
{
    val->path = getpath(tab, val->env);
    if (val->path != NULL) {
        *last_status = use_fork(val->path, tab, linked_list);
        free_tab_and_path(tab, val->path);
    } else {
        mini_printf("%s: Command not found.\n", tab[0]);
        free_tab_and_path(tab, NULL);
        *last_status = 1;
    }
    return;
}

int verif_entry(char **tab, linked_list_t **linked_list
    , stock_str_t *val, int *last_status)
{
    int redirection_status = 1;
    int status = recup_status(tab, val, linked_list);

    if (status == 0 || status == 3)
        return status;
    redirection_status = handle_redirections(tab, val->env, linked_list, val);
    *last_status = redirection_status;
    if (redirection_status == 0 || redirection_status == 1)
        return write_free(tab, val);
    *last_status = check_command(tab, val->env, linked_list);
    if (*last_status == 0 || *last_status == 1)
        return write_free(tab, val);
    check_fork(tab, linked_list, val, last_status);
    return 1;
}

static int return_result(char ***tabu,
    linked_list_t **linked_list, stock_str_t val, int *last_status)
{
    int result = 0;

    for (int i = 0; tabu[i] != NULL; i++) {
        result = verif_entry(tabu[i], linked_list, &val, last_status);
        if (result == 3 || result == 0)
            return result;
    }
    return 1;
}

int relaunch_program(linked_list_t **linked_list, char *buffer
    , char **env, int *last_status)
{
    char ***tabu = NULL;
    stock_str_t val = {buffer, env, NULL};
    int result = 0;

    if (my_strlen(buffer) > 1) {
        tabu = create_tab(buffer);
        if (tabu == NULL)
            return 84;
        result = return_result(tabu, linked_list, val, last_status);
        if (result == 3 || result == 0)
            return result;
        free(tabu);
    }
    if (isatty(0))
        write(1, "$> ", 3);
    return 1;
}

int start_programm(int ac, char **av)
{
    if (ac != 1 || av[1] != NULL)
        return 84;
    if (isatty(0))
        write(1, "$> ", 3);
    return 0;
}

int main(int ac, char **av, char **env)
{
    char *buffer = NULL;
    linked_list_t *linked_list = NULL;
    value_return_t val = {0, 0};
    int last_status = 0;

    linked_list = add_linked_list(linked_list, env);
    if (start_programm(ac, av) == 84)
        return 84;
    while (getline(&buffer, &val.len, stdin) != -1) {
        buffer[my_strlen(buffer) - 1] = '\0';
        val.result = relaunch_program(&linked_list, buffer, env, &last_status);
        if (!isatty(0) && last_status != 0)
            return last_status;
        if (val.result == 84 || val.result == 3) {
            free(buffer);
            return last_status;
        }
    }
    free(buffer);
    return last_status;
}
