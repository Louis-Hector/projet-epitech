/*
** EPITECH PROJECT, 2023
** B-CPE-110 : organized
** File description:
** organized.c
*/

#include "include/mystruct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libshell/shell.h"
#include "include/my.h"


int disp(void *data, char **args)
{
    linked_node_t *list = *(linked_node_t **)data;
    int count = 0;

    for (int i = 0; args[i] != NULL; i++)
        count++;
    if (count > 0)
        return 84;
    while (list != NULL) {
        mini_printf("%s n°%d - \"%s\"\n",
            display_type(list->type), list->num, list->name);
        list = list->next;
    }
    return 0;
}

int main(int ac, char **av)
{
    linked_node_t *link = NULL;

    if (ac > 1)
        return 84;
    return workshop_shell(&link);
}
