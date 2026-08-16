/*
** EPITECH PROJECT, 2025
** create_env.c
** File description:
** create environnemt with linked list
*/

#include "shell.h"

/**
 * @brief Allocates memory for the environment variable and assigns values.
 *
 * This function allocates memory for the environment variable string,
 * copies the key and value, and appends a null terminator.
 *
 * @param current The current environment variable node.
 * @param env The array of environment variables.
 * @param i The index of the environment variable in the array.
 * @return 0 on success, 84 on memory allocation failure.
 */
int affect_value_env(env_t *current, char **env, int i)
{
    if (current->key != NULL && current->value != NULL)
        env[i] = malloc(sizeof(char) *
            (strlen(current->key) + strlen(current->value) + 2));
    if (current->key != NULL && current->value == NULL)
        env[i] = malloc(sizeof(char) * (strlen(current->key) + 2));
    if (env[i] == NULL)
        return 84;
    if (current->key != NULL)
        strcpy(env[i], current->key);
    strcat(env[i], "=");
    if (current->value != NULL)
        strcat(env[i], current->value);
    strcat(env[i], "\0");
    return 0;
}

/**
 * @brief Converts a linked list of environment variables to an array.
 *
 * This function iterates through the linked list of environment variables,
 * allocates memory for an array, and copies the key-value into the array.
 *
 * @param envi The head of the linked list of environment variables.
 * @return A pointer to the array of environment variables.
 */
char **from_list_to_array(env_t **envi)
{
    env_t *head = *envi;
    env_t *current = *envi;
    char **env = NULL;
    int i = 0;

    for (i = 0; head; i++)
        head = head->next;
    env = malloc(sizeof(char *) * (i + 1));
    if (env == NULL)
        return NULL;
    for (i = 0; current; i++) {
        if (affect_value_env(current, env, i) == 84)
            return NULL;
        current = current->next;
    }
    env[i] = NULL;
    return env;
}
