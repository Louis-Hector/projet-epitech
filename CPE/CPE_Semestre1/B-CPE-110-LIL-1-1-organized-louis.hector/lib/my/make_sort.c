/*
** EPITECH PROJECT, 2023
** B-CPE-110 : make_sort.c
** File description:
** make the sort for the worksop
*/

#include "../../include/mystruct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../libshell/shell.h"
#include "my.h"

static void assign_values_name(linked_node_t *actual, linked_node_t *sort)
{
    linked_node_t *pro = NULL;

    pro = sort;
    while (pro->next != NULL && my_strcmp(pro->next->name, actual->name) < 0)
        pro = pro->next;
    actual->next = pro->next;
    pro->next = actual;
}

void sort_name(linked_node_t **list)
{
    linked_node_t *sort = NULL;
    linked_node_t *next = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;
    for (linked_node_t *actual = *list; actual != NULL;) {
        next = actual->next;
        if (sort == NULL || my_strcmp(sort->name, actual->name) > 0) {
            actual->next = sort;
            sort = actual;
        } else {
            assign_values_name(actual, sort);
        }
        actual = next;
    }
    *list = sort;
}

static void assign_values_type(linked_node_t *actual, linked_node_t *sort)
{
    linked_node_t *pro = NULL;

    pro = sort;
    while (pro->next != NULL && pro->next->type < actual->type)
        pro = pro->next;
    actual->next = pro->next;
    pro->next = actual;
}

void sort_type(linked_node_t **list)
{
    linked_node_t *sort = NULL;
    linked_node_t *next = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;
    for (linked_node_t *actual = *list; actual != NULL;) {
        next = actual->next;
        if (sort == NULL || sort->type > actual->type) {
            actual->next = sort;
            sort = actual;
        } else {
            assign_values_type(actual, sort);
        }
        actual = next;
    }
    *list = sort;
}

static void assign_values_id(linked_node_t *actual, linked_node_t *sort)
{
    linked_node_t *pro = NULL;

    pro = sort;
    while (pro->next != NULL && pro->next->num < actual->num)
        pro = pro->next;
    actual->next = pro->next;
    pro->next = actual;
}

void sort_id(linked_node_t **list)
{
    linked_node_t *sort = NULL;
    linked_node_t *next = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;
    for (linked_node_t *actual = *list; actual != NULL;) {
        next = actual->next;
        if (sort == NULL || sort->num > actual->num) {
            actual->next = sort;
            sort = actual;
        } else {
            assign_values_id(actual, sort);
        }
        actual = next;
    }
    *list = sort;
}

static void relaunch_loop(linked_node_t **list, char **tab, int valid, int i)
{
    if (valid) {
        sort_reverse(list, tab[i]);
    } else {
        if (my_strcmp(tab[i], "NAME") == 0)
            sort_name(list);
        if (my_strcmp(tab[i], "TYPE") == 0)
            sort_type(list);
        if (my_strcmp(tab[i], "ID") == 0)
            sort_id(list);
    }
}

static int check_error_handling(char **args, char **tab)
{
    int count = 0;

    if (tab == NULL)
        return 84;
    for (int i = 0; args[i] != NULL; i++)
        count++;
    if (count == 0)
        return 84;
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "NAME") != 0
            && my_strcmp(args[i], "ID") != 0
            && my_strcmp(args[i], "TYPE") != 0
            && my_strcmp(args[i], "-r") != 0)
        return 84;
    }
    return 0;
}

int sort(void *data, char **args)
{
    linked_node_t **list = (linked_node_t **)data;
    int valid = 0;
    char **tab = malloc(sizeof(char *) * 100);
    int count = 0;

    if (check_error_handling(args, tab) == 84)
        return 84;
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "-r") == 0)
            valid = 1;
        if (my_strcmp(args[i], "NAME") == 0
            || my_strcmp(args[i], "ID") == 0
            || my_strcmp(args[i], "TYPE") == 0) {
            tab[count] = args[i];
            count++;
        }
    }
    for (int i = 0; i < count; i++)
        relaunch_loop(list, tab, valid, i);
    return 0;
}
