/*
** EPITECH PROJECT, 2023
** B-CPE-110 : make_add.C
** File description:
** make the add for the worksop
*/

#include "../../include/mystruct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../libshell/shell.h"
#include "my.h"


enum type check_type(char *item)
{
    if (my_strcmp(item, "ACTUATOR") == 0)
        return ACTUATOR;
    if (my_strcmp(item, "DEVICE") == 0)
        return DEVICE;
    if (my_strcmp(item, "PROCESSOR") == 0)
        return PROCESSOR;
    if (my_strcmp(item, "SENSOR") == 0)
        return SENSOR;
    if (my_strcmp(item, "WIRE") == 0)
        return WIRE;
    return 84;
}

char *display_type(type_t type)
{
    char *name[5] = {"ACTUATOR", "DEVICE", "PROCESSOR", "SENSOR", "WIRE"};

    for (int i = 0; i < 5; i++) {
        if (type == i)
            return name[i];
    }
    return NULL;
}

static int add_node(linked_node_t **begin, char *surname, type_t item, int num)
{
    linked_node_t *list = malloc(sizeof(linked_node_t));

    if (list == NULL)
        return 84;
    list->next = *begin;
    list->name = surname;
    list->num = num;
    list->type = item;
    *begin = list;
    mini_printf("%s n°%d - \"%s\" added.\n",
        display_type(list->type), list->num, list->name);
    return 0;
}

int check_error(char **args)
{
    int count = 0;
    int number = 0;

    for (int i = 0; args[i] != NULL; i++)
        number++;
    if (number == 0)
        return 84;
    for (int a = 0; args[a] != NULL; a++)
        count++;
    if (count % 2 != 0)
        return 84;
    else
        return 0;
}

int add(void *data, char **args)
{
    linked_node_t **begin = (linked_node_t **)data;
    static int nume = 0;
    char *surname;
    char *p;
    type_t item;

    if (check_error(args) == 84)
        return 84;
    for (int i = 0; args[i] != NULL; i += 2) {
        p = my_strdup(args[i]);
        surname = my_strdup(args[i + 1]);
        item = check_type(p);
        if (p == NULL || surname == NULL)
            return 84;
        if (item == 84 || args[i + 1] == NULL)
            return 84;
        add_node(begin, surname, item, nume++);
        free(p);
    }
    return 0;
}
