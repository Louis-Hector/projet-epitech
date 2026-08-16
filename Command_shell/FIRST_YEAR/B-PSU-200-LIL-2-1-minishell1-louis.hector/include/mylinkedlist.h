/*
** EPITECH PROJECT, 2025
** linkedlist command for mysh
** File description:
** setenv, env...
*/


#ifndef MYLIK_H_
    #define MYLIK_H_

    #include "my.h"
    #include <stdlib.h>

typedef struct linked_list_s {
    char *value;
    char *key;
    struct linked_list_s *next;
} linked_list_t;

typedef struct stock_str_s {
    char *buffer;
    char **env;
    char *path;
} stock_str_t;


typedef struct value_return_s {
    size_t len;
    int result;
} value_return_t;

linked_list_t *add_linked_list(linked_list_t *list, char **env);
int make_env(linked_list_t **list, char **tab);
int make_setenv(linked_list_t **list, char **tab);
int check_command(char **tab, char **env, linked_list_t **linked_list);
void free_linked_list(linked_list_t **list);
int make_unsetenv(linked_list_t **list, char **tab);
char *getpath(char **tab, char **env);
int change_directory(char **tab, char **env);
int use_fork(char *path, char **tab, linked_list_t **linked_list);
char **create_environnement(linked_list_t **list);
void free_tab_and_path(char **tab, char *path);

#endif
