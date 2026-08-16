/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** create_linked_list
*/

#include "shell.h"

/**
 * @brief Creates a new node in the linked list and assigns values to it.
 *
 * This function allocates memory for a new node, splits the environment
 * variable string into key and value, and assigns them to the node.
 *
 * @param line The environment variable string.
 * @param env The array of environment variables.
 * @param node The node to be created.
 * @param i The index of the environment variable in the array.
 * @return A pointer to the newly created node.
 */
static env_t *affect_node(char *line, char **env, env_t *node, int i)
{
    char *cpy_ev = strdup(env[i]);

    line = (strtok(cpy_ev, "="));
    if (line == NULL)
        node->key = strdup("");
    else
        node->key = strdup(line);
    line = (strtok(NULL, "\n"));
    if (line == NULL)
        node->value = strdup("");
    else
        node->value = strdup(line);
    node->next = NULL;
    free(cpy_ev);
    return node;
}

/**
 * @brief Converts an array of environment variables to a linked list.
 *
 * This function iterates through the array of environment variables,
 * creates a new node for each variable, and links them together in a list.
 *
 * @param list The head of the linked list.
 * @param env The array of environment variables.
 * @return A pointer to the head of the linked list.
 */
env_t *from_array_to_list(env_t *list, char **env)
{
    env_t *node = NULL;
    env_t *last_node = NULL;
    char *line = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        node = malloc(sizeof(env_t));
        if (node == NULL)
            return NULL;
        node->key = NULL;
        node->value = NULL;
        if (affect_node(line, env, node, i) == NULL)
            return NULL;
        if (list == NULL)
            list = node;
        else
            last_node->next = node;
        last_node = node;
    }
    return list;
}
