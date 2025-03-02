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

static void reverse_values_name(linked_node_t *actual, linked_node_t *sort)
{
    linked_node_t *pro = NULL;

    pro = sort;
    while (pro->next != NULL && my_strcmp(pro->next->name, actual->name) > 0)
        pro = pro->next;
    actual->next = pro->next;
    pro->next = actual;
}

void reverse_sort_name(linked_node_t **list)
{
    linked_node_t *sort = NULL;
    linked_node_t *next = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;
    for (linked_node_t *actual = *list; actual != NULL;) {
        next = actual->next;
        if (sort == NULL || my_strcmp(sort->name, actual->name) < 0) {
            actual->next = sort;
            sort = actual;
        } else {
            reverse_values_name(actual, sort);
        }
        actual = next;
    }
    *list = sort;
}

static void reverse_values_type(linked_node_t *actual, linked_node_t *sort)
{
    linked_node_t *pro = NULL;

    pro = sort;
    while (pro->next != NULL && pro->next->type > actual->type)
        pro = pro->next;
    actual->next = pro->next;
    pro->next = actual;
}

void reverse_sort_type(linked_node_t **list)
{
    linked_node_t *sort = NULL;
    linked_node_t *next = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;
    for (linked_node_t *actual = *list; actual != NULL;) {
        next = actual->next;
        if (sort == NULL || sort->type < actual->type) {
            actual->next = sort;
            sort = actual;
        } else {
            reverse_values_type(actual, sort);
        }
        actual = next;
    }
    *list = sort;
}

static void reverse_values_id(linked_node_t *actual, linked_node_t *sort)
{
    linked_node_t *pro = NULL;

    pro = sort;
    while (pro->next != NULL && pro->next->num > actual->num)
        pro = pro->next;
    actual->next = pro->next;
    pro->next = actual;
}

void reverse_sort_id(linked_node_t **list)
{
    linked_node_t *sort = NULL;
    linked_node_t *next = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;
    for (linked_node_t *actual = *list; actual != NULL;) {
        next = actual->next;
        if (sort == NULL || sort->num < actual->num) {
            actual->next = sort;
            sort = actual;
        } else {
            reverse_values_id(actual, sort);
        }
        actual = next;
    }
    *list = sort;
}

void sort_reverse(linked_node_t **list, char *tab)
{
    if (my_strcmp(tab, "NAME") == 0)
        reverse_sort_name(list);
    if (my_strcmp(tab, "ID") == 0)
        reverse_sort_id(list);
    if (my_strcmp(tab, "TYPE") == 0)
        reverse_sort_type(list);
}
