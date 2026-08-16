/*
** EPITECH PROJECT, 2025
** command_fonctions.c
** File description:
** create command fonctions
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include <string.h>
#include "mylinkedlist.h"

int verif_second_arg(char **previous_path, char **tab, char *path, char *cwd)
{
    if (tab[1] == NULL || my_strcmp(tab[1], "~") == 0) {
        if (*previous_path != NULL)
            free(*previous_path);
        *previous_path = my_strdup(cwd);
        if (chdir(path) == -1)
            return 1;
        return 0;
    }
    if (tab[1] != NULL && my_strcmp(tab[1], "~")
        != 0 && my_strcmp(tab[1], "-") != 0) {
        if (*previous_path != NULL)
            free(*previous_path);
        *previous_path = my_strdup(cwd);
        if (chdir(tab[1]) == -1) {
            mini_printf("%s: No such file or directory.\n", tab[1]);
            return 1;
        }
        return 0;
    }
    return 1;
}

int check_type_directory(char **tab, char *path)
{
    static char *previous_path = NULL;
    char cwd[500];
    int result = 0;

    getcwd(cwd, sizeof(cwd));
    result = verif_second_arg(&previous_path, tab, path, cwd);
    if (result == 0)
        return 0;
    if (tab[1] != NULL && my_strcmp(tab[1], "-") == 0) {
        if (previous_path != NULL) {
            chdir(previous_path);
            free(previous_path);
            previous_path = NULL;
            return 0;
        }
    }
    return result;
}

int check_number_arg(char **tab)
{
    int count = 0;

    for (int i = 0; tab[i] != NULL; i++)
        count++;
    if (count > 2) {
        mini_printf("cd: Too many arguments.\n");
        return 1;
    }
    return 0;
}

int change_directory(char **tab, char **env)
{
    char *line = NULL;
    char *path = NULL;
    int result = 0;

    if (check_number_arg(tab) == 1)
        return 1;
    for (int i = 0; env[i] != NULL; i++)
        if (my_strncmp(env[i], "HOME=", 5) == 0)
            line = my_strdup(env[i]);
    if (line != NULL) {
        path = strtok(line, "=");
        path = strtok(NULL, "\n");
    } else
        return 1;
    result = check_type_directory(tab, path);
    free(line);
    return result;
}

int check_command(char **tab, char **env, linked_list_t **linked_list)
{
    if (my_strcmp(tab[0], "cd") == 0) {
        return change_directory(tab, env);
    }
    if (my_strcmp(tab[0], "env") == 0) {
        return make_env(linked_list, tab);
    }
    if (my_strcmp(tab[0], "setenv") == 0) {
        return make_setenv(linked_list, tab);
    }
    if (my_strcmp(tab[0], "unsetenv") == 0) {
        return make_unsetenv(linked_list, tab);
    }
    return -1;
}
