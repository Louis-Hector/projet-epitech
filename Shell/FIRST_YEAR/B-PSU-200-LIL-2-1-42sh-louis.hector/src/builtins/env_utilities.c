/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** env_commands.c
*/

#include "shell.h"

/**
 * @brief Insert a new environment variable into the linked list.
 *
 * This function creates a new node for the environment variable
 * and inserts it at the end of the linked list.
 *
 * @param head Pointer to the head of the linked list.
 * @param name The name of the environment variable.
 * @param data The value of the environment variable.
 */
static void insert_in_list(env_t **head, char *name, char *data)
{
    env_t *temp = malloc(sizeof(env_t));
    env_t *current = NULL;

    if (!temp)
        return;
    temp->key = strdup(name);
    temp->value = strdup(data);
    temp->next = NULL;
    if (*head == NULL)
        *head = temp;
    else {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = temp;
    }
}

/**
 * @brief Find an environment variable by name and update its value.
 *
 * This function searches for an environment variable in the linked list
 * by its name. If found, it updates its value with the provided data.
 *
 * @param env_list Pointer to the head of the linked list.
 * @param name The name of the environment variable to find.
 * @param data The new value to set for the environment variable.
 * @return 1 if the variable was found and updated, 0 otherwise.
 */
static int find_name(env_t *env_list, char *name, char *data)
{
    while (env_list != NULL) {
        if (strcmp(env_list->key, name) == 0) {
            free(env_list->value);
            env_list->value = strdup(data);
            return 1;
        }
        env_list = env_list->next;
    }
    return 0;
}

/**
 * @brief Check if a string contains only alphanumeric characters.
 *
 * This function checks if the given string contains only alphanumeric
 * characters (letters, digits, '_', and '.') and returns 1 if it does,
 * otherwise returns 0.
 *
 * @param str The string to check.
 * @return 1 if the string is alphanumeric, 0 otherwise.
 */
static int is_alphanum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < 'a' || str[i] > 'z') &&
            (str[i] < 'A' || str[i] > 'Z') &&
            (str[i] < '0' || str[i] > '9') &&
            str[i] != '_' && str[i] != '.')
            return 1;
    }
    return 0;
}

/**
 * @brief Check if the environment variable name is valid and insert it.
 *
 * This function checks if the environment variable name is valid
 * (starts with a letter and contains only alphanumeric characters).
 * If valid, it inserts the variable into the linked list.
 *
 * @param arg The command arguments.
 * @param env Pointer to the head of the linked list.
 * @return 0 if the variable was inserted, 1 if there was an error.
 */
int is_data_present(char **arg, env_t **env)
{
    if (arg[1] != NULL && arg[2] != NULL) {
        if ((arg[1][0] >= '0' && arg[1][0] <= '9')
            || strcmp(arg[1], "\"\"") == 0) {
            dprintf(2, "setenv: Variable name must begin with a letter.\n");
            return 1;
        }
        if ((is_alphanum(arg[1]) == 1)
            && strcmp(arg[1], "\"\"") != 0) {
            dprintf(2, "setenv: Variable name"
            " must contain alphanumeric characters.\n");
            return 1;
        }
        if (!find_name(*env, arg[1], arg[2])) {
            insert_in_list(env, arg[1], arg[2]);
            return 0;
        }
    }
    return 0;
}

/**
 * @brief Check if the environment variable name is valid and insert it.
 *
 * This function checks if the environment variable name is valid
 * (starts with a letter and contains only alphanumeric characters).
 * If valid, it inserts the variable into the linked list.
 *
 * @param arg The command arguments.
 * @param env Pointer to the head of the linked list.
 * @return 0 if the variable was inserted, 1 if there was an error.
 */
int is_data_missing(char **arg, env_t **env)
{
    if (arg[1] != NULL && arg[2] == NULL) {
        if ((arg[1][0] >= '0' && arg[1][0] <= '9')) {
            dprintf(2, "setenv: Variable name must begin with a letter.\n");
            return 1;
        }
        if (is_alphanum(arg[1]) == 1) {
            dprintf(2, "setenv: Variable name must"
            " contain alphanumeric characters.\n");
            return 1;
        }
        if (!find_name(*env, arg[1], "\0")) {
            insert_in_list(env, arg[1], "\0");
            return 0;
        }
    }
    return 0;
}

/**
 * @brief Check the number of arguments for the setenv command.
 *
 * This function checks if the number of arguments for the setenv command
 * is valid. If there are too many arguments, it prints an error message.
 * If no arguments are provided, it prints all environment variables.
 *
 * @param env Pointer to the head of the linked list.
 * @param nb_arg The number of arguments passed to the command.
 * @param arg The command arguments.
 * @return 1 if there are too many arguments, 0 otherwise.
 */
int check_arg_number(env_t **env, int nb_arg, char **arg)
{
    env_t *env_list = *env;

    if (nb_arg > 3) {
        dprintf(2, "setenv: Too many arguments.\n");
        return 1;
    }
    if (arg[1] == NULL) {
        while (env_list != NULL) {
            printf("%s=%s\n", env_list->key, env_list->value);
            env_list = env_list->next;
        }
        return 0;
    }
    return 0;
}

/**
 * @brief Remove a node from the linked list.
 *
 * This function removes a node from the linked list by updating the
 * pointers of the previous and current nodes. It also frees the memory
 * allocated for the node's key and value.
 *
 * @param current Pointer to the current node to remove.
 * @param prev Pointer to the previous node.
 * @param head Pointer to the head of the linked list.
 */
void remove_node(env_t **current, env_t **prev, env_t **head)
{
    if (*prev == NULL) {
        *head = (*current)->next;
        free((*current)->key);
        free((*current)->value);
        free(*current);
        *current = *head;
    } else {
        (*prev)->next = (*current)->next;
        free((*current)->key);
        free((*current)->value);
        free(*current);
        *current = (*prev)->next;
    }
}
