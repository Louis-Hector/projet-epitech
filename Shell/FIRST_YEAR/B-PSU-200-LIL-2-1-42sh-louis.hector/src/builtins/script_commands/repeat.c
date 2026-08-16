/*
** EPITECH PROJECT, 2025
** repeat
** File description:
** repeat
*/

#include "shell.h"

/**
 * @brief Check if a string is a valid number.
 *
 * This function checks if the given string represents a valid number.
 * It allows negative numbers and checks for digits only.
 *
 * @param str The string to check.
 * @return 1 if the string is a valid number, 0 otherwise.
 */
static int is_numeric(char *str)
{
    int i = 0;

    if (str && str[0] == '-')
        i = 1;
    for (; str[i]; i++) {
        if (!isdigit(str[i])) {
            dprintf(2, "repeat: Badly formed number.\n");
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Recover the node and execute the repeat command.
 *
 * This function recovers the node and executes the repeat command
 * by checking everything in the node and freeing allocated memory.
 *
 * @param shell The shell structure.
 * @param env The environment variables.
 * @param node The command node to recover.
 * @param tab The array of command line arguments.
 * @return 0 on success, 1 on failure.
 */
static int recover_node(shell_t *shell, env_t **env
    , command_t *node, char **tab)
{
    int j = 2;
    int a = 0;

    for (; tab[j] != NULL; j++) {
        node->args[a] = strdup(tab[j]);
        if (verif_maloc(node->args[a], shell)) {
            free(node->args);
            free(node);
            return 1;
        }
        a++;
    }
    node->args[a] = NULL;
    for (int i = 0; i < shell->repeat; i++)
        check_everything(node, env, shell);
    free_array(node->args);
    free(node);
    return 0;
}

/**
 * @brief Execute the repeat command.
 *
 * This function executes the repeat command by checking the number
 * of arguments and recovering the node for execution.
 *
 * @param shell The shell structure.
 * @param args The array of command line arguments.
 * @param env The environment variables.
 * @return 0 on success, 1 on failure.
 */
int execute_repeat(shell_t *shell
    , char **args, env_t **env)
{
    int count = 0;
    command_t *node = malloc(sizeof(command_t));

    if (verif_maloc(node, shell))
        return 1;
    for (int a = 2; args[a] != NULL; a++)
        count++;
    if (count == 0) {
        free_array(args);
        free(node);
        return 0;
    }
    node->args = malloc(sizeof(char *) * (count + 1));
    if (verif_maloc(node->args, shell))
        return 1;
    return recover_node(shell, env, node, args);
}

/**
 * @brief Repeat a command a specified number of times.
 *
 * This function checks the number of arguments and verifies if the
 * first argument is a valid number. If valid, it sets the repeat
 * count and executes the repeat command.
 *
 * @param tab The array of command line arguments.
 * @param env The environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 * @return 0 on success, 1 on failure.
 */
int repeat_command(char **tab, env_t **env, char **old_path, shell_t *shell)
{
    int count = 0;

    if (!tab || !env || !old_path || !shell)
        return 0;
    for (count = 0; tab[count] != NULL; count++);
    if (count <= 2) {
        dprintf(2, "repeat: Too few arguments.\n");
        shell->return_value = 1;
        return 1;
    }
    if (!is_numeric(tab[1]))
        return 1;
    shell->repeat = atoi(tab[1]);
    execute_repeat(shell, tab, env);
    return 0;
}
