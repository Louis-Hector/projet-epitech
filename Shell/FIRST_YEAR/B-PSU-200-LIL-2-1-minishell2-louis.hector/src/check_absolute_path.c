/*
** EPITECH PROJECT, 2025
** l.c
** File description:
** verif malloc and free...
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include <signal.h>
#include <string.h>
#include "mylinkedlist.h"

int make_signal(int status)
{
    if (WTERMSIG(status) == SIGSEGV) {
        mini_printf("Segmentation fault (core dumped)\n");
        return 139;
    }
    if (WTERMSIG(status) == SIGFPE) {
        mini_printf("Floating exception (core dumped)\n");
        return 136;
    }
    if (WTERMSIG(status) == SIGABRT) {
        mini_printf("Aborted (core dumped)\n");
        return 1;
    }
    return 0;
}

static int value_fork_execve(pid_t pid, char *path, char **av, char **env)
{
    if (pid == 0) {
        if (execve(path, av, env) == -1) {
            mini_printf("%s: Exec format error. "
                "Binary file not executable.\n", av[0]);
            return 1;
        }
        return 0;
    }
    return 1;
}

int verif_pid(pid_t pid, char **av, char **env, char *path)
{
    int value = 0;
    int signal = 0;

    if (pid > 0) {
        waitpid(pid, &value, 0);
        signal = make_signal(value);
        if (signal == 139 || signal == 1 || signal == 136)
            return signal;
        if (value != 0)
            return 2;
        return 0;
    }
    if (value_fork_execve(pid, path, av, env) == 0)
        return 0;
    return 1;
}

int use_fork(char *path, char **av, linked_list_t **linked_list)
{
    pid_t pid = fork();
    char **env = create_environnement(linked_list);
    int value = 0;

    if (env == NULL)
        return 2;
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    value = verif_pid(pid, av, env, path);
    if (env != NULL) {
        for (int i = 0; env[i] != NULL; i++)
            free(env[i]);
        free(env);
    }
    return value;
}

char *check_dir(char *dir, char *path, char **tab, char *check)
{
    while (dir != NULL) {
        check = malloc(my_strlen(dir) + my_strlen(tab[0]) + 2);
        if (check == NULL) {
            free(path);
            return NULL;
        }
        my_strcpy(check, dir);
        my_strcat(check, "/");
        my_strcat(check, tab[0]);
        if (access(check, F_OK) == 0) {
            free(path);
            return check;
        }
        dir = strtok(NULL, ":");
        free(check);
    }
    free(path);
    return NULL;
}

char *getpath(char **tab, char **env)
{
    char *path = NULL;
    char *check = NULL;
    char *dir = NULL;

    if (access(tab[0], F_OK) == 0)
        return my_strdup(tab[0]);
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0) {
            path = my_strdup(env[i] + 5);
            break;
        }
    }
    dir = strtok(path, ":");
    check = check_dir(dir, path, tab, check);
    if (check == NULL)
        return NULL;
    return check;
}
