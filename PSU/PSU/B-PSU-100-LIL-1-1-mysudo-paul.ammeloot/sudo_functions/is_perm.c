/*
** EPITECH PROJECT, 2025
** is_perm.c
** File description:
** is_perm
*/

#include "../include/my.h"
#include <string.h>
#include <stdlib.h>

static int verif_sudoers(char *line, char *name, char *buffer, FILE *fd)
{
    char **tab = NULL;

    tab = my_str_to_word_array(line, '\t');
    if (tab != NULL && my_strcmp(tab[0], name) == 0) {
        free(tab);
        free(buffer);
        fclose(fd);
        return 0;
    }
    free(tab);
    return 1;
}

int is_name_found(char **user, char *name)
{
    for (int i = 0; user[i] != NULL; i++) {
        if (my_strcmp(user[i], name) == 0) {
            return 0;
        }
    }
    return 84;
}

static int is_in_valid_group(char **tab, char *name, char *group)
{
    char **user;
    char *without_back_slash_n;
    int len = 0;

    if (tab[0] == NULL || tab[3] == NULL)
        return 84;
    if (my_strcmp(tab[0], group) == 0) {
        len = strlen(tab[3]);
        without_back_slash_n = malloc(sizeof(char *) * (len - 1));
        for (int i = 0; tab[3][i] != '\n'; i++)
            without_back_slash_n[i] = tab[3][i];
        without_back_slash_n[strlen(tab[3]) - 1] = '\0';
        user = my_str_to_word_array(without_back_slash_n, ',');
        if (is_name_found(user, name) == 0) {
            free(user);
            return 0;
        }
    }
    return 84;
}

int is_in_sudo_groups(char *name, char *group)
{
    FILE *fd = fopen("/etc/group", "r");
    char *buffer = NULL;
    size_t size = 0;
    char **tab = NULL;

    if (fd == NULL)
        return 84;
    while (getline(&buffer, &size, fd) != -1) {
        tab = my_str_to_word_array(buffer, ':');
        if (tab != NULL && is_in_valid_group(tab, name, group) == 0) {
            free(tab);
            free(buffer);
            fclose(fd);
            return 0;
        }
        free(tab);
    }
    free(buffer);
    fclose(fd);
    return 84;
}

int check_line(char *line, char *name)
{
    char group[100];

    if (line[0] == '%') {
        sscanf(line, "%%%s", group);
        if (is_in_sudo_groups(name, group) == 0)
            return 0;
    }
    if (verif_sudoers(line, name, NULL, NULL) == 0)
        return 0;
    return 84;
}

int is_in_sudoers(char *name)
{
    FILE *fd = fopen("/etc/sudoers", "r");
    char *buffer = NULL;
    size_t size = 0;
    char *line = NULL;
    int result = 84;

    if (fd == NULL)
        return 84;
    while (getline(&buffer, &size, fd) != -1) {
        line = strtok(buffer, "\n");
        if (line && check_line(line, name) == 0) {
            result = 0;
            break;
        }
    }
    free(buffer);
    fclose(fd);
    return result;
}

int check_sudoers(char *name)
{
    if (is_in_sudoers(name) == 84) {
        printf("%s is not in the my_sudoers file.\n", name);
        return 84;
    }
    return 0;
}
