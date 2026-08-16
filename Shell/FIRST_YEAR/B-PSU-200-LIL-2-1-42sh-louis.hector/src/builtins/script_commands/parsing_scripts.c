/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** parsing_scripts.c
*/

#include "shell.h"

/**
 * @brief Print an error message based on the number of parentheses.
 *
 * This function checks the number of opening and closing parentheses
 * in the command line. If there are too many or not enough, it prints
 * an error message and sets the return value in the shell structure.
 *
 * @param parent_open The number of opening parentheses.
 * @param parent_close The number of closing parentheses.
 * @param shell The shell structure.
 * @return 1 if there is an error, 0 otherwise.
 */
static int print_error(int parent_open, int parent_close, shell_t *shell)
{
    if (parent_open != 1 || parent_close != 1
        || parent_close > 2 || parent_open > 2) {
        dprintf(2, "Too many ('s.\n");
        shell->return_value = 1;
        return 1;
    }
    if (parent_open == 0 && parent_close == 0) {
        dprintf(2, "foreach: Words not parenthesized.\n");
        shell->return_value = 1;
        return 1;
    }
    return 0;
}

/**
 * @brief Verify the first argument of the foreach command.
 *
 * This function checks if the first argument of the foreach command
 * is valid. It counts the number of arguments and checks for parentheses.
 *
 * @param args The array of command line arguments.
 * @param shell The shell structure.
 * @return 1 if there is an error, 0 otherwise.
 */
int verify_first_argument(char **args, shell_t *shell)
{
    int count = 0;
    int parent_open = 0;
    int parent_close = 0;

    for (int i = 0; args[i] != NULL; i++)
        count++;
    if (count < 3) {
        dprintf(2, "foreach: Too few arguments.\n");
        shell->return_value = 1;
        return 1;
    }
    for (size_t i = 2; args[i] != NULL; i++) {
        for (size_t j = 0; args[i][j] != '\0'; j++) {
            parent_open += (args[i][j] == '(') ? 1 : 0;
            parent_close += (args[i][j] == ')') ? 1 : 0;
        }
    }
    return print_error(parent_open, parent_close, shell);
}

/**
 * @brief Create a new command string from the array of arguments.
 *
 * This function concatenates the arguments in the array into a single
 * command string, separating them with spaces. It also frees the original
 * array and the variable used for replacement.
 *
 * @param tabs The array of command line arguments.
 * @param count The total length of the new command string.
 * @param shell The shell structure.
 * @param var The variable used for replacement.
 * @return A pointer to the newly created command string.
 */
static char *create_new_command(char **tabs, size_t count
    , shell_t *shell, char *var)
{
    char *new_line = NULL;

    new_line = malloc(count + 1);
    if (verif_maloc(new_line, shell)) {
        free_array(tabs);
        free(var);
        return NULL;
    }
    new_line[0] = '\0';
    for (int i = 0; tabs[i]; i++) {
        strcat(new_line, tabs[i]);
        if (tabs[i + 1])
            strcat(new_line, " ");
    }
    free_array(tabs);
    free(var);
    return new_line;
}

/**
 * @brief Replace the variable in the command line with its value.
 *
 * This function replaces the variable in the command line with its
 * corresponding value. It creates a new command string with the
 * replaced value and frees the original array and variable.
 *
 * @param line The original command line.
 * @param name The name of the variable to replace.
 * @param shell The shell structure.
 * @param args The array of command line arguments.
 * @return A pointer to the new command string with the replaced value.
 */
char *replace_dollar(char *line, char *name, shell_t *shell, char **args)
{
    char *var = malloc(strlen(args[1]) + 2);
    size_t count = 0;
    char **tabs = NULL;

    if (verif_maloc(var, shell))
        return NULL;
    snprintf(var, strlen(args[1]) + 2, "$%s", args[1]);
    tabs = my_str_to_word_array(line, " \t");
    if (verif_maloc(tabs, shell)) {
        free(var);
        return NULL;
    }
    for (int i = 0; tabs[i]; i++) {
        if (strcmp(tabs[i], var) == 0) {
            free(tabs[i]);
            tabs[i] = strdup(name);
        }
        count += strlen(tabs[i]) + 1;
    }
    return create_new_command(tabs, count, shell, var);
}

/**
 * @brief Verify if the memory allocation was successful.
 *
 * This function checks if the memory allocation for an element was
 * successful. If not, it sets the return value in the shell structure
 * to 84 and returns 1.
 *
 * @param element The element to check.
 * @param shell The shell structure.
 * @return 1 if there was an error, 0 otherwise.
 */
int verif_maloc(void *element, shell_t *shell)
{
    if (element == NULL) {
        if (shell)
            shell->return_value = 84;
        return 1;
    }
    return 0;
}

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
int initialize_commands(foreach_t *foreach, shell_t *shell)
{
    foreach->commands = NULL;
    foreach->commands = malloc(sizeof(char *) * (128 + 1));
    if (verif_maloc(foreach->commands, shell))
        return 1;
    return 0;
}
