/*
** EPITECH PROJECT, 2025
** environemnt_command.c
** File description:
** env, setenv linked list fonctions
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include <signal.h>
#include <string.h>
#include "mylinkedlist.h"

int count_arg_setenv(char **tab, linked_list_t *node)
{
    if (!((tab[1][0] >= 'A' && tab[1][0] <= 'Z')
        || (tab[1][0] >= 'a' && tab[1][0] <= 'z'))) {
            mini_printf("setenv: Variable name must begin with a letter.\n");
            return 1;
    }
    for (int i = 1; tab[1][i] != '\0'; i++) {
        if (!((tab[1][i] >= 'A' && tab[1][i] <= 'Z')
            || (tab[1][i] >= 'a' && tab[1][i] <= 'z')
            || (tab[1][i] >= '0' && tab[1][i] <= '9')
            || tab[1][i] == '.' || tab[1][i] == '_')) {
            mini_printf("setenv: Variable name must "
                "contain alphanumeric characters.\n");
            return 1;
        }
    }
    if (tab[1] != NULL && tab[2] != NULL) {
        node->key = my_strdup(tab[1]);
        node->value = my_strdup(tab[2]);
    }
    return 0;
}

int verif_existence(char **tab, linked_list_t *node
    , linked_list_t **list)
{
    int count = 0;

    for (int i = 0; tab[i] != NULL; i++)
        count++;
    if (count == 1) {
        make_env(list, tab);
        return 0;
    }
    if (count > 3) {
        mini_printf("setenv: Too many arguments.\n");
        return 1;
    }
    if (count_arg_setenv(tab, node) == 1)
        return 1;
    if (tab[2] == NULL) {
        node->key = my_strdup(tab[1]);
        node->value = my_strdup("");
    }
    return 0;
}

int make_setenv(linked_list_t **list, char **tab)
{
    linked_list_t *current = *list;
    linked_list_t *node = malloc(sizeof(linked_list_t));
    int value = 0;

    if (node == NULL)
        return 84;
    value = verif_existence(tab, node, list);
    if (value == 1) {
        return value;
    }
    node->next = NULL;
    if (current == NULL)
        *list = node;
    else {
        while (current->next != NULL)
            current = current->next;
        current->next = node;
    }
    return value;
}

void make_header(linked_list_t *previous, linked_list_t *current
    , linked_list_t *to_delete, linked_list_t **list)
{
    if (previous == NULL)
        *list = current->next;
    else
        previous->next = current->next;
    to_delete = current;
    current = current->next;
    free(to_delete);
}

int make_unsetenv(linked_list_t **list, char **tab)
{
    linked_list_t *to_delete = NULL;
    linked_list_t *current = *list;
    linked_list_t *previous = NULL;

    if (tab[1] == NULL) {
        mini_printf("unsetenv: Too few arguments.\n");
        return 1;
    }
    while (current != NULL) {
        if (my_strcmp(current->key, tab[1]) == 0) {
            make_header(previous, current, to_delete, list);
            return 0;
        } else {
            previous = current;
            current = current->next;
        }
    }
    return 0;
}
