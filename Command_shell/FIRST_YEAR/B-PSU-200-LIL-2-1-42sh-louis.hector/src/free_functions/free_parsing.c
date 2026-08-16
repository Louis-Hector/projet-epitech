/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** free_parsing
*/

#include "shell.h"

/**
 * @brief Free all nodes in a linked list of environment variables.
 *
 * This function iterates through the linked list of environment variables,
 * freeing all dynamically allocated keys, values, and nodes.
 *
 * @param list Pointer to the head of the linked list to be freed.
 */
void free_linked_list(env_t **list)
{
    env_t *current = *list;
    env_t *previous = NULL;

    while (current != NULL) {
        previous = current;
        current = current->next;
        if (previous->key != NULL)
            free(previous->key);
        if (previous->value != NULL)
            free(previous->value);
        free(previous);
    }
}

/**
 * @brief Free all nodes in a linked list of commands.
 *
 * This function iterates through the linked list of commands, freeing
 * dynamically allocated file names, argument arrays, and nodes.
 *
 * @param commands Pointer to the head of the command list to be freed.
 */
void free_command(command_t **commands)
{
    command_t *tmp = *commands;
    command_t *next_tmp = NULL;

    while (tmp) {
        next_tmp = tmp->next;
        if (tmp->file)
            free(tmp->file);
        if (tmp->args)
            free_array(tmp->args);
        free(tmp);
        tmp = next_tmp;
    }
    *commands = NULL;
}

/**
 * @brief Free a dynamically allocated array of strings.
 *
 * This function frees each string in the array and then the array itself.
 *
 * @param array Pointer to the array of strings to be freed.
 */
void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

/**
 * @brief Free all nodes in a linked list of aliases.
 *
 * This function traverses the alias linked list and frees all dynamically
 * allocated memory associated with each alias, including the alias name,
 * its value, and the node itself.
 *
 * @param alias A pointer to the head pointer of the alias linked list.
 */
void free_alias(alias_t **alias)
{
    alias_t *current = *alias;
    alias_t *previous = NULL;

    while (current != NULL) {
        previous = current;
        current = current->next;
        if (previous->alias != NULL)
            free(previous->alias);
        if (previous->value != NULL)
            free(previous->value);
        free(previous);
    }
}

/**
 * @brief Free all nodes in a linked list of environment variables.
 *
 * This function is similar to `free_linked_list`, iterating through a linked
 * list of environment variables and freeing keys, values, and nodes.
 *
 * @param node Pointer to the head of the linked list to be freed.
 */
void is_free(env_t **node, shell_t *shell_arg)
{
    env_t *tmp = *node;
    env_t *next_tmp = NULL;

    while (tmp){
        next_tmp = tmp->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
        tmp = next_tmp;
    }
    free_alias(&shell_arg->alias);
    if (shell_arg->file->credits)
        fclose(shell_arg->file->credits);
    if (shell_arg->file->dragon)
        fclose(shell_arg->file->dragon);
    if (shell_arg->file->epitech)
        fclose(shell_arg->file->epitech);
    free(shell_arg->file);
}
