/*
** EPITECH PROJECT, 2025
** crete_tab.C
** File description:
** create_tab
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include <signal.h>
#include <string.h>
#include "mylinkedlist.h"

int relauch_command(char *command, char ***tab, create_tab_av_t *test)
{
    char **list_command = NULL;

    while (command != NULL) {
        list_command = my_str_to_word_array(command);
        if (list_command == NULL) {
            free(tab);
            return 84;
        }
        tab[test->i] = list_command;
        test->i++;
        command = strtok(NULL, ";");
    }
    return 0;
}

char ***create_tab(char *buffer)
{
    char ***tab = NULL;
    create_tab_av_t test = {0};
    char *command = NULL;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ';')
            test.count++;
    }
    tab = malloc(sizeof(char **) * (test.count + 2));
    if (tab == NULL)
        return NULL;
    command = strtok((buffer), ";");
    if (relauch_command(command, tab, &test) == 84)
        return NULL;
    tab[test.i] = NULL;
    return tab;
}
