/*
** EPITECH PROJECT, 2023
** B-CPE-110 : make_del.c
** File description:
** make the del for the worksop
*/

#include "../../include/mystruct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../libshell/shell.h"
#include "my.h"

void print_del(linked_node_t *previous, linked_node_t *actuelle
    , linked_node_t **begin, int number)
{
    linked_node_t *temp = NULL;

    if (actuelle->num == number) {
        mini_printf("%s n°%d - \"%s\" deleted.\n",
            display_type(actuelle->type), actuelle->num, actuelle->name);
        if (previous == NULL)
            *begin = actuelle->next;
        else
            previous->next = actuelle->next;
        temp = actuelle;
        actuelle = actuelle->next;
        free(temp);
    } else {
        previous = actuelle;
        actuelle = actuelle->next;
    }
}

void check_actual(linked_node_t **previous, linked_node_t **actuelle)
{
    if (*actuelle != NULL) {
        *previous = *actuelle;
        *actuelle = (*actuelle)->next;
    }
}

int make_loop(char **args, int i)
{
    for (int j = 0; j < my_strlen(args[i]); j++) {
            if (args[i][j] < '0' || args[i][j] > '9')
                return 84;
    }
    return 0;
}

int check_handling(char **args)
{
    int number = 0;

    for (int i = 0; args[i] != NULL; i++)
        number++;
    if (number == 0)
        return 84;
    for (int i = 0; args[i] != NULL; i++) {
        if (make_loop(args, i) == 84)
            return 84;
    }
    return 0;
}

int del(void *data, char **args)
{
    linked_node_t **begin = (linked_node_t **)data;
    linked_node_t *actuelle = *begin;
    linked_node_t *previous = NULL;
    int number = 0;

    if (check_handling(args) == 84)
        return 84;
    for (int i = 0; args[i] != NULL; i++) {
        number = my_getnbr(args[i]);
        actuelle = *begin;
        previous = NULL;
        while (actuelle != NULL) {
            print_del(previous, actuelle, begin, number);
            check_actual(&previous, &actuelle);
        }
    }
    return 0;
}
