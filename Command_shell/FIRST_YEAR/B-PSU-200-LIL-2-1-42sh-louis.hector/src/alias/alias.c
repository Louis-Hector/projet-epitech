/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** alias.c
*/

#include "shell.h"

/**
  *@brief Add a new alias to the alias linked list.
  *
  *This function creates a new alias node and adds it to the end of the alias
  *linked list. The alias consists of a name and its corresponding value.
  *
  *@param alias A pointer to the head of the alias linked list.
  *@param alias_name The name of the alias.
  *@param value The value of the alias.
  *@param alias_path The path to the alias file (optional, can be NULL).
  *
  *@return 0 on success, 1 on failure.
*/
int add_alias(alias_t **alias, char *alias_name, char *value)
{
    alias_t *new_alias = malloc(sizeof(alias_t));
    alias_t *current = NULL;

    if (!new_alias || alias_name == NULL || value == NULL)
        return 1;
    new_alias->alias = strdup(alias_name);
    new_alias->value = strdup(value);
    if (!*alias)
        *alias = new_alias;
    else {
        current = *alias;
        while (current->next != NULL)
            current = current->next;
        current->next = new_alias;
    }
    new_alias->next = NULL;
    return 1;
}

/**
 * @brief Updates the head or previous pointer when deleting an alias node.
 *
 * This helper function updates the alias linked list when a node is deleted.
 * It also frees the memory allocated for the deleted alias node.
 *
 * @param current The alias node to delete.
 * @param alias A pointer to the head pointer of the alias linked list.
 * @param tmp A pointer to the next node after the current one.
 * @param prev A pointer to the previous node before the current one.
 */
static void verif_head_list(alias_t *current, alias_t **alias
    , alias_t *tmp, alias_t *prev)
{
    if (prev == NULL)
        *alias = tmp;
    else
        prev->next = tmp;
    free(current->alias);
    free(current->value);
    free(current);
}

/**
  *@brief Delete a specific alias node from the alias linked list.
  *
  *This function removes a specific alias node from the linked list and frees
  *its memory.
  *
  *@param alias A pointer to the head of the alias linked list.
  *@param current The alias node to delete.
  *@param prev The previous alias node in the list.
*/
void delete_alias_node(alias_t **alias, char **tab, int i)
{
    alias_t *current = *alias;
    alias_t *prev = NULL;
    alias_t *tmp = NULL;

    while (current != NULL) {
        if (strcmp(current->alias, tab[i]) == 0) {
            tmp = current->next;
            verif_head_list(current, alias, tmp, prev);
            current = tmp;
            continue;
        }
        prev = current;
        current = current->next;
    }
}

/**
 * @brief Removes one or more aliases from the alias linked list.
 *
 * This function iterates over the array `tab` which contains the names
 * of the aliases to be removed.
 *
 * @param alias A pointer to the head of the alias linked list.
 * @param tab An array of strings containing the alias names to remove.
 */
static int remove_alias(alias_t **alias, char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        delete_alias_node(alias, tab, i);
    return 1;
}

/**
 * @brief Displays all aliases currently stored in the alias linked list.
 *
 * This function iterates over the alias linked list and prints each alias
 * along with its corresponding value to the standard output.
 *
 * @param alias A pointer to the head of the alias linked list.
 * @return Always returns 1 (used as a success indicator).
 */
static int print_alias(alias_t **alias, shell_t *shell)
{
    alias_t *current = *alias;

    shell->return_value = 0;
    while (current != NULL) {
        printf("%s   %s\n", current->alias, current->value);
        current = current->next;
    }
    return 1;
}

/**
  *@brief Handle alias or unalias commands from user input.
  *
  *This function checks if the input corresponds to an "alias" or "unalias"
  *command and performs the appropriate action.
  *
  *@param alias A pointer to the head of the alias linked list.
  *@param input The user input string.
  *@param alias_path The path to the alias file.
  *
  *@return 1 on success, 0 on failure, 84 on memory allocation error.
*/
int check_alias_cmd(alias_t **alias, char **tab, shell_t *shell)
{
    int count = 0;

    for (; tab[count] != NULL; count++);
    if (strcmp(tab[0], "alias") == 0 && count == 1)
        return print_alias(alias, shell);
    if (strcmp(tab[0], "alias") == 0) {
        shell->return_value = 0;
        return add_alias(alias, tab[1], tab[2]);
    }
    if (strcmp(tab[0], "unalias") == 0) {
        if (count <= 1) {
            fprintf(stderr, "unalias: Too few arguments.\n");
            shell->return_value = 1;
            return 1;
        }
        shell->return_value = 0;
        return remove_alias(alias, tab);
    }
    return 0;
}

/**
 * @brief Checks if the alias matches and replaces the command argument.
 *
 * This function compares the alias name (`current->alias`) with `tab[0]`.
 * If a match is found, it replaces `tab[0]`
 *
 * @param current The current alias node in the alias linked list.
 * @param tab The array of command arguments.
 * @param shell The shell structure, used for setting error codes.
 *
 * @return 1 if an alias was found and replaced, 0 otherwise.
 */
int find_alias_in_cmd(alias_t *current, char **tab, shell_t *shell)
{
    if (strcmp(current->alias, tab[0]) == 0) {
        free(tab[0]);
        tab[0] = malloc(sizeof(char) * (strlen(current->value) + 1));
        if (tab[0] == NULL) {
            shell->return_value = 1;
            return 1;
        }
        strcpy(tab[0], current->value);
        return 1;
    }
    return 0;
}

/**
 * @brief Iterates through the alias list and modifies the command argument.
 *
 * This function goes through the alias linked list and checks each alias using
 * `find_alias_in_cmd`. If an alias is found, it replaces the corresponding
 * command argument (`tab[0]`).
 *
 * @param alias The head of the alias linked list.
 * @param tab The array of command arguments.
 * @param shell The shell structure, used to set error codes.
 */
void modif_alias_cmd(alias_t **alias, char **tab, shell_t *shell)
{
    alias_t *current = *alias;

    shell->return_value = 0;
    while (current != NULL) {
        if (find_alias_in_cmd(current, tab, shell) == 1)
            return;
        current = current->next;
    }
    return;
}
