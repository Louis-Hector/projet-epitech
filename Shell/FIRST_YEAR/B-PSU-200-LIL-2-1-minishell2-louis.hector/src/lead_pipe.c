/*
** EPITECH PROJECT, 2025
** lead_pipe.c
** File description:
** affect pipe
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include <signal.h>
#include <string.h>
#include "mylinkedlist.h"


static int make_pid(stock_str_t *val, char **tab)
{
    val->path = getpath(tab, val->env);
    if (val->path != NULL) {
        execve(val->path, tab, val->env);
        mini_printf("%s: Exec format error. "
            "Binary file not executable.\n", tab[0]);
        return 1;
    } else {
        mini_printf("%s: Command not found.\n", tab[0]);
        exit(1);
    }
    return 0;
}

int make_first_pid(int tube[2], char **tab, int index, stock_str_t *val)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return 1;
    if (pid == 0) {
        close(tube[0]);
        if (dup2(tube[1], STDOUT_FILENO) == -1)
            return 1;
        close(tube[1]);
        tab[index] = NULL;
        val->path = getpath(tab, val->env);
        if (make_pid(val, tab) == 1)
            return 1;
    }
    return 0;
}

int make_second_pid(int tube[2], char **second_element, stock_str_t *val)
{
    pid_t pid2;

    pid2 = fork();
    if (pid2 == -1)
        return 1;
    if (pid2 == 0) {
        close(tube[1]);
        if (dup2(tube[0], STDIN_FILENO) == -1)
            return 1;
        close(tube[0]);
        if (make_pid(val, second_element) == 1)
            return 1;
    }
    return 0;
}

void free_second_element(char **second_element)
{
    if (second_element == NULL)
        return;
    for (int i = 0; second_element[i] != NULL; i++)
        free(second_element[i]);
    free(second_element);
}

char **recup_second_element(char **tab, int index)
{
    char **second_element = NULL;
    int count = 0;
    int a = 0;

    for (int i = index + 1; tab[i] != NULL; i++)
        count++;
    second_element = malloc(sizeof(char *) * (count + 1));
    if (second_element == NULL)
        return NULL;
    for (int b = index + 1; tab[b] != NULL; b++) {
        second_element[a] = my_strdup(tab[b]);
        if (second_element[a] == NULL) {
            free_second_element(second_element);
            return NULL;
        }
        a++;
    }
    second_element[a] = NULL;
    return second_element;
}

int affect_pipe(char **tab, int index
    , linked_list_t **linked_list, stock_str_t *val)
{
    int tube[2];
    char **second_element = recup_second_element(tab, index);

    if (second_element == NULL)
        return 1;
    pipe(tube);
    if (make_first_pid(tube, tab, index, val) == 1) {
        free_second_element(second_element);
        return 1;
    }
    if (make_second_pid(tube, second_element, val) == 1) {
        free_second_element(second_element);
        return 1;
    }
    free_second_element(second_element);
    close(tube[0]);
    close(tube[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
