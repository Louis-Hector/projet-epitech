/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** where.c
*/

#include "shell.h"

/**
 * @brief Count the number of arguments for the where command.
 *
 * This function checks if the number of arguments for the where command
 * is valid. If there are too few arguments, it prints an error message.
 * If the PATH environment variable is not set, it also sets the return value.
 *
 * @param tabs The array of command line arguments.
 * @param shell The shell structure.
 * @param path_env The PATH environment variable.
 * @return 1 if there are too few arguments or if PATH is NULL, 0 otherwise.
 */
int count_args_where(char **tabs, shell_t *shell, char *path_env)
{
    if (tabs[1] == NULL) {
        dprintf(2, "where: Too few arguments.\n");
        shell->return_value = 1;
        return 1;
    }
    if (path_env == NULL) {
        shell->return_value = 1;
        return 1;
    }
    return 0;
}

/**
 * @brief Verify the command path.
 *
 * This function checks if the command exists in the specified directory.
 * If it does, it prints the full path of the command.
 *
 * @param direct The directory to check.
 * @param tabs The array of command line arguments.
 * @param shell The shell structure.
 * @param i The index of the current argument.
 * @return 0 if successful, 1 if an error occurs.
 */
int verif_command_path(char *direct, char **tabs, shell_t *shell, int *i)
{
    char *check = NULL;
    int len = 0;

    while (direct != NULL) {
        len = strlen(direct) + strlen(tabs[*i]) + 2;
        check = malloc(sizeof(char) * len);
        if (!check) {
            shell->return_value = 84;
            return 1;
        }
        snprintf(check, len, "%s/%s", direct, tabs[*i]);
        if (access(check, F_OK) == 0)
            printf("%s\n", check);
        free(check);
        direct = strtok(NULL, ":");
    }
    *i += 1;
    shell->return_value = 0;
    return 0;
}

/**
 * @brief Create a copy of the PATH environment variable.
 *
 * This function creates a copy of the PATH environment variable and
 * checks if the command is "echo". If it is, it prints a message.
 *
 * @param copy Pointer to the copy of the PATH variable.
 * @param path_env The PATH environment variable.
 * @param shell The shell structure.
 * @param tab The array of command line arguments.
 * @return 0 on success, 1 on failure.
 */
int create_copy_path_env(char **copy, char *path_env
    , shell_t *shell, char **tab)
{
    if (strcmp(tab[1], "echo") == 0)
        printf("echo is a shell built-in\n");
    *copy = strdup(path_env);
    if (!*copy) {
        shell->return_value = 84;
        return 1;
    }
    return 0;
}

/**
 * @brief Check if the command is a built-in command.
 *
 * This function checks if the command is a built-in command and
 * prints a message if it is. It also increments the index of the
 * current argument.
 *
 * @param tabs The array of command line arguments.
 * @param index_args Pointer to the index of the current argument.
 * @return 1 if the command is a built-in, 0 otherwise.
 */
int confirm_builtins_command(char **tabs, int *index_args)
{
    char *builtins_command[7] = {"cd", "where", "exit", "history",
        "setenv", "unsetenv", "foreach"};

    for (int i = 0; i < 7; i++) {
        if (strcmp(builtins_command[i], tabs[*index_args]) == 0) {
            printf("%s is a shell built-in\n", tabs[*index_args]);
            *index_args += 1;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Find the path of a command.
 *
 * This function searches for the path of a command in the directories
 * specified in the PATH environment variable. It prints the full path
 * if found, otherwise it prints an error message.
 *
 * @param tabs The array of command line arguments.
 * @param env The environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 * @return 0 on success, 1 on failure.
 */
int find_where(char **tabs, env_t **env, char **old_path, shell_t *shell)
{
    char *path_env = getenv("PATH");
    char *copy = NULL;
    int index_args = 1;
    char *directory = NULL;

    if (count_args_where(tabs, shell, path_env) == 1 || !env || !old_path)
        return 1;
    while (tabs[index_args] != NULL) {
        if (confirm_builtins_command(tabs, &index_args) == 1)
            continue;
        if (create_copy_path_env(&copy, path_env, shell, tabs) == 1)
            return 1;
        directory = strtok(copy, ":");
        if (verif_command_path(directory, tabs, shell, &index_args) == 1) {
            free(copy);
            return 1;
        }
        free(copy);
    }
    return 0;
}
