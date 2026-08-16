/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** foreach.c
*/

#include "shell.h"

/**
 * @brief Initialize the commands array in the foreach structure.
 *
 * This function allocates memory for the commands array in the
 * foreach structure. It initializes it to NULL and checks for
 * successful memory allocation.
 *
 * @param foreach The foreach structure to initialize.
 * @param shell The shell structure.
 * @return 0 on success, 1 on failure.
 */
int recup_info_foreach(foreach_t *foreach, shell_t *shell, int *i)
{
    char *line = NULL;
    size_t size = 0;

    if (initialize_commands(foreach, shell) == 1)
        return 1;
    while (1) {
        printf("foreach? ");
        if (getline(&line, &size, stdin) == -1)
            break;
        if (strlen(line) < 1)
            continue;
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, "end") == 0)
            break;
        foreach->commands[*i] = strdup(line);
        *i += 1;
    }
    foreach->commands[*i] = NULL;
    free(line);
    return 0;
}

/**
 * @brief Allocate memory for the list of variables in the foreach structure.
 *
 * This function allocates memory for the list of variables in the
 * foreach structure and checks for successful memory allocation.
 *
 * @param tab The array of strings to copy into the list.
 * @param shell The shell structure.
 * @param list_in_var The list of variables to fill.
 * @return 0 on success, 1 on failure.
 */
static int affect_value_in_list(char **tab, shell_t *shell, char **list_in_var)
{
    int i = 0;

    for (i = 0; tab[i]; i++) {
        (list_in_var)[i] = strdup(tab[i]);
        if (!(list_in_var)[i]) {
            free_array(tab);
            free_array(list_in_var);
            shell->return_value = 84;
            return 1;
        }
    }
    (list_in_var)[i] = NULL;
    free_array(tab);
    return 0;
}

/**
 * @brief Recover the list of variables from the input string.
 *
 * This function splits the input string into an array of strings
 * and allocates memory for the list of variables. It checks for
 * successful memory allocation and fills the list with the values.
 *
 * @param list_var The input string containing the list of variables.
 * @param shell The shell structure.
 * @param list_in_var The list of variables to fill.
 * @return 0 on success, 1 on failure.
 */
static int recover_list_var(char *list_var,
    shell_t *shell, char ***list_in_var)
{
    char **tab = my_str_to_word_array(list_var, " ");
    int count = 0;

    if (!tab) {
        shell->return_value = 84;
        return 1;
    }
    for (; tab[count]; count++);
    *list_in_var = malloc(sizeof(char *) * (count + 1));
    if (!*list_in_var) {
        free_array(tab);
        shell->return_value = 84;
        return 1;
    }
    return affect_value_in_list(tab, shell, *list_in_var);
}

/**
 * @brief Free the memory allocated for the foreach structure.
 *
 * This function frees the memory allocated for the list of variables,
 * commands, and line. It returns 0 if end is 0, otherwise it returns 1.
 *
 * @param tab The list of variables to free.
 * @param commands_line The list of commands to free.
 * @param line The line to free.
 * @param end The end condition.
 * @return 0 if end is 0, 1 otherwise.
 */
int free_foreach(char **tab, char **commands_line, char *line, int end)
{
    if (tab != NULL)
        free_array(tab);
    if (commands_line != NULL)
        free_array(commands_line);
    if (line != NULL)
        free(line);
    if (end == 0)
        return 0;
    else
        return 1;
}

/**
 * @brief Recover the node and execute the command line.
 *
 * This function allocates memory for the command node and fills it
 * with the arguments from the input string. It checks for successful
 * memory allocation and executes the command line.
 *
 * @param shell The shell structure.
 * @param env The environment variables.
 * @param node The command node to fill.
 * @param tab The array of command line arguments.
 * @return 0 on success, 1 on failure.
 */
int recover_node_args(shell_t *shell, env_t **env
    , command_t *node, char **tab)
{
    int j = 0;

    for (j = 0; tab[j] != NULL; j++) {
        node->args[j] = strdup(tab[j]);
        if (verif_maloc(node->args[j], shell)) {
            free_array(tab);
            free(node->args);
            free(node);
            return 1;
        }
    }
    node->args[j] = NULL;
    check_everything(node, env, shell);
    free_array(node->args);
    free_array(tab);
    free(node);
    return 0;
}

/**
 * @brief Execute the command line by creating a new command node.
 *
 * This function creates a new command node and fills it with the
 * arguments from the input string. It checks for successful memory
 * allocation and executes the command line.
 *
 * @param shell The shell structure.
 * @param line_replace The input string containing the command line.
 * @param env The environment variables.
 * @return 0 on success, 1 on failure.
 */
int execute_command_line(shell_t *shell
    , char *line_replace, env_t **env)
{
    char **tab = NULL;
    int count = 0;
    command_t *node = malloc(sizeof(command_t));

    tab = my_str_to_word_array(line_replace, " ");
    if (verif_maloc(tab, shell) || verif_maloc(node, shell))
        return 1;
    for (int a = 0; tab[a] != NULL; a++)
        count++;
    if (count == 0) {
        free_array(tab);
        free(node);
        return 0;
    }
    node->args = malloc(sizeof(char *) * (count + 1));
    if (verif_maloc(node->args, shell))
        return 1;
    return recover_node_args(shell, env, node, tab);
}

/**
 * @brief Launch the command line for each variable in the list.
 *
 * This function iterates through the list of variables and executes
 * the command line for each variable. It checks for successful memory
 * allocation and handles errors.
 *
 * @param f The foreach structure containing the list of variables.
 * @param args The array of command line arguments.
 * @param shell The shell structure.
 * @param env The environment variables.
 * @return 0 on success, 1 on failure.
 */
static int launch_command(foreach_t *f, char **args
    , shell_t *shell, env_t **env)
{
    for (int i = 0; f->commands[i] != NULL; i++) {
        f->line = replace_dollar(f->commands[i]
            , f->list[f->index_var], shell, args);
        if (f->line == NULL)
            return free_foreach(f->list, f->commands, NULL, 1);
        if (execute_command_line(shell, f->line, env) == 1)
            return free_foreach(f->list, f->commands, f->line, 1);
        free(f->line);
    }
    return 0;
}

/**
 * @brief Remove parentheses from the list variable string.
 *
 * This function removes the opening and closing parentheses from
 * the list variable string if they exist.
 *
 * @param list_var The input string containing the list variable.
 * @return A pointer to the modified string without parentheses.
 */
static char *remove_parent(char *list_var)
{
    if (list_var[0] == '(')
        memmove(list_var, list_var + 1, strlen(list_var));
    if (list_var[strlen(list_var) - 1] == ')')
        list_var[strlen(list_var) - 1] = '\0';
    return list_var;
}

/**
 * @brief Create a list variable from the input arguments.
 *
 * This function creates a list variable by concatenating the
 * arguments from the input string. It checks for successful memory
 * allocation and handles errors.
 *
 * @param args The array of command line arguments.
 * @param shell The shell structure.
 * @return A pointer to the created list variable string.
 */
static char *create_list_var(char **args, shell_t *shell)
{
    char *list_var = NULL;
    int count = 0;

    if (get_array_size(args) < 3) {
        dprintf(2, "foreach: Too few arguments.\n");
        shell->return_value = 1;
        return NULL;
    }
    for (int i = 2; args[i]; i++)
        count += (strlen(args[i]) + 1);
    list_var = malloc(sizeof(char) * count);
    if (verif_maloc(list_var, shell))
        return NULL;
    list_var[0] = '\0';
    for (int i = 2; args[i]; i++) {
        strcat(list_var, args[i]);
        if (args[i + 1])
            strcat(list_var, " ");
    }
    return remove_parent(list_var);
}

/**
 * @brief Find and execute the foreach command.
 *
 * This function creates a list variable from the input arguments,
 * recovers the list of variables, and executes the command line
 * for each variable in the list.
 *
 * @param args The array of command line arguments.
 * @param env The environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 * @return 0 on success, 1 on failure.
 */
int find_foreach(char **args, env_t **env, char **old_path, shell_t *shell)
{
    char *list_parent = create_list_var(args, shell);
    foreach_t f = {0};
    int i = 0;

    if (!env || !old_path || list_parent == NULL)
        return 1;
    if (verify_first_argument(args, shell) == 1
        || recover_list_var(list_parent, shell, &f.list) == 1
        || recup_info_foreach(&f, shell, &i) == 1) {
        free(list_parent);
        return 1;
    }
    for (int j = 0; f.list[j] != NULL; j++) {
        f.index_var = j;
        if (launch_command(&f, args, shell, env) == 1)
            return 1;
    }
    shell->return_value = 0;
    return free_foreach(f.list, f.commands, list_parent, 0);
}
