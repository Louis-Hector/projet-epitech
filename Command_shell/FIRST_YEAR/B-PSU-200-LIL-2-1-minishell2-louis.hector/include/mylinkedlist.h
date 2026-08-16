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

typedef struct create_tab_av_s {
    int index;
    int count;
    int i;
    char **command;
} create_tab_av_t;

typedef struct direction_s {
    int i;
    char **tab;
} direction_t;

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
char ***create_tab(char *buffer);
int handle_redirections(char **tab, char **env
    , linked_list_t **linked_list, stock_str_t *val);
int affect_pipe(char **tab, int index,
    linked_list_t **linked_list, stock_str_t *val);
#endif
