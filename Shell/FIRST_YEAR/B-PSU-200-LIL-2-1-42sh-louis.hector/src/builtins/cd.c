/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** cd_functions
*/

#include "shell.h"

/**
 * @brief Change the current working directory to the specified path.
 *
 * This function changes the current working directory to the specified path
 * and returns the status of the operation.
 *
 * @param array The array containing the path to change to.
 * @param path The current working directory.
 * @return The status of the chdir operation (0 on success, -1 on error).
 */
static int cd_wave(char **array, char *path)
{
    int len_path = strlen(path);
    int len_secpath = strlen(array[1]);
    char *new_path = malloc(sizeof(char) * (len_secpath));
    int status = 0;
    char *all_path = malloc(sizeof(char) * (len_path + len_secpath));

    if (!new_path || !all_path) {
        free(new_path);
        free(all_path);
        return -1;
    }
    for (int i = 1; i < len_secpath; i++)
        new_path[i - 1] = array[1][i];
    new_path[len_secpath - 1] = '\0';
    strcpy(all_path, path);
    strcat(all_path, new_path);
    status = chdir(all_path);
    free(all_path);
    free(new_path);
    return status;
}

/**
 * @brief Execute a simple change directory command.
 *
 * This function checks if the specified path is a directory and changes
 * the current working directory to that path.
 *
 * @param old_path Pointer to the old path to store the previous directory.
 * @param tab The array containing the command arguments.
 * @param cwd The current working directory.
 * @return 0 on success, 1 on error.
 */
static int exec_simple_cd(char **old_path,
    char **tab, char *cwd)
{
    DIR *is_dir = NULL;

    if (tab[1] != NULL && strcmp(tab[1], "~")
        != 0 && strcmp(tab[1], "-") != 0) {
        if (*old_path != NULL)
            free(*old_path);
        *old_path = strdup(cwd);
        is_dir = opendir(tab[1]);
        if (!is_dir) {
            dprintf(2, "%s: Not a directory.\n", tab[1]);
            return 1;
        }
        closedir(is_dir);
        if (chdir(tab[1]) == -1) {
            dprintf(2, "%s: No such file or directory.\n", tab[1]);
            return 1;
        }
        return 0;
    }
    return 1;
}

/**
 * @brief Verify the second argument of the change directory command.
 *
 * This function checks if the second argument is NULL or "~" and
 * changes the current working directory accordingly.
 *
 * @param old_path Pointer to the old path to store the previous directory.
 * @param tab The array containing the command arguments.
 * @param path The current working directory.
 * @param cwd The current working directory.
 * @return 0 on success, 1 on error.
 */
static int verif_second_arg(char **old_path,
    char **tab, char *path, char *cwd)
{
    if (tab[1] == NULL || strcmp(tab[1], "~") == 0) {
        if (*old_path != NULL)
            free(*old_path);
        *old_path = strdup(cwd);
        if (chdir(path) == -1)
            return 1;
        return 0;
    }
    if (strncmp(tab[1], "~/", 2) == 0) {
        if (*old_path != NULL)
            free(*old_path);
        *old_path = strdup(cwd);
        if (cd_wave(tab, path) == -1)
            return 1;
        return 0;
    }
    return exec_simple_cd(old_path, tab, cwd);
}

/**
 * @brief Check if the second argument is a directory and change to it.
 *
 * This function checks if the second argument is a directory and changes
 * the current working directory to that path. If the second argument is
 * "-", it changes back to the previous directory.
 *
 * @param tab The array containing the command arguments.
 * @param path The current working directory.
 * @param old_path Pointer to the old path to store the previous directory.
 * @return 0 on success, 1 on error.
 */
static int check_type_directory(char **tab, char *path, char **old_path)
{
    char cwd[500];
    int result = 0;

    getcwd(cwd, sizeof(cwd));
    result = verif_second_arg(old_path, tab, path, cwd);
    if (result == 0)
        return 0;
    if (tab[1] != NULL && strcmp(tab[1], "-") == 0) {
        if (*old_path != NULL) {
            chdir(*old_path);
            free(*old_path);
            *old_path = NULL;
            return 0;
        }
    }
    return result;
}

/**
 * @brief Check if the specified path is a valid directory.
 *
 * This function checks if the specified path is a valid directory and
 * if the user has permission to access it.
 *
 * @param args The array containing the command arguments.
 * @return 0 if the path is valid, 1 if not.
 */
static int check_option(char **args)
{
    struct stat sb = {0};

    if (args[1] && args[2]) {
        dprintf(2, "cd: Too many arguments.\n");
        return 1;
    }
    if (!args[1] || strncmp(args[1], "~", 1) == 0 ||
        strncmp(args[1], "-", 1) == 0)
        return 0;
    if (lstat(args[1], &sb) == -1) {
        dprintf(2, "%s: No such file or directory.\n", args[1]);
        return 1;
    }
    if (S_ISDIR(sb.st_mode))
        if (access(args[1], X_OK) != 0) {
            dprintf(2, "%s: Permission denied.\n", args[1]);
            return 1;
        }
    return 0;
}

/**
 * @brief Change the shell prompt to the current working directory.
 *
 * This function updates the shell prompt to include the current working
 * directory followed by a ">" character.
 *
 * @param shell The shell structure containing the prompt.
 */
static void change_prompt(shell_t *shell)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        free(shell->prompt);
        strcat(cwd, ">");
        shell->prompt = strdup(cwd);
        return;
    }
}

/**
 * @brief Change the current working directory to the home directory.
 *
 * This function changes the current working directory to the home directory
 * specified in the environment variables or to the default home directory.
 *
 * @param tab The array containing the command arguments.
 * @param env The environment variables.
 * @param old_path Pointer to the old path to store the previous directory.
 * @param shell The shell structure.
 * @return 0 on success, 1 on error.
 */
int change_directory(char **tab, env_t **env, char **old_path, shell_t *shell)
{
    char *line = NULL;
    int result = 0;
    env_t *env_list = *env;

    if (check_option(tab) == 1) {
        shell->return_value = 1;
        return 1;
    }
    for (; env_list; env_list = env_list->next)
        if (strncmp(env_list->key, "HOME", 4) == 0)
            line = strdup(env_list->value);
    if (line == NULL)
        line = get_home_user("/");
    if (line == NULL)
        return 1;
    result = check_type_directory(tab, line, old_path);
    shell->return_value = result;
    free(line);
    change_prompt(shell);
    return result;
}
