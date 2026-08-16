/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** command_basics.c
*/

#include "shell.h"

/**
 * @brief Display error messages related to command execution.
 *
 * This function handles various error scenarios related to command execution,
 * including invalid file format, signal termination,
 * and floating point exceptions.
 *
 * @param status Status code returned by the executed process.
 * @param file File name causing the execution error (optional).
 * @return Returns 128 + signal number for signaled processes,
 *         the exit status for exited processes, or 1 otherwise.
 */
int display_error(int status, char *file)
{
    if (file != NULL) {
        dprintf(2, "%s: Exec format error."
        " Binary file not executable.\n", file);
            exit(1);
    }
    if (WIFSIGNALED(status)) {
        if (__WCOREDUMP(status) && WTERMSIG(status) != SIGFPE)
            dprintf(2, "%s (core dumped)\n", strsignal(WTERMSIG(status)));
        if (!__WCOREDUMP(status) && WTERMSIG(status) != SIGFPE)
            dprintf(2, "%s\n", strsignal(WTERMSIG(status)));
        if (__WCOREDUMP(status) && WTERMSIG(status) == SIGFPE)
            dprintf(2, "Floating exception (core dumped)\n");
        if (!__WCOREDUMP(status) && WTERMSIG(status) == SIGFPE)
            dprintf(2, "Floating exception\n");
        return 128 + WTERMSIG(status);
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}

/**
 * @brief Handle process execution and error scenarios for a duplicate process.
 *
 * This function uses 'execve' to execute the command, handling errors such as
 * invalid executable files, missing files, or permission issues.
 *
 * @param path_with_function Full path to the executable.
 * @param current Pointer to the current command structure.
 * @param env Array of environment variables.
 */
static int handle_duplicate_processus(char *path_with_function,
    command_t *current, char **env)
{
    execve(path_with_function, current->args, env);
    if (errno == ENOEXEC)
        display_error(0, current->args[0]);
    if (errno == ENOENT)
        exit(127);
    dprintf(2, "%s: Permission denied.\n", current->args[0]);
    exit(1);
}

/**
 * @brief Fork a new process and execute the command.
 *
 * This function creates a new process using 'fork',
 * executes the command in the child, process, and waits for its completion
 * in the parent process. Errors during execution are handled appropriately.
 *
 * @param path_with_function Full path to the executable.
 * @param current Pointer to the current command structure.
 * @param env Array of environment variables.
 * @return Returns 0 on successful execution, 1 on failure.
 */
int split_fork(char *path_with_function, command_t *current, char **env)
{
    pid_t new_pid = fork();
    int status = 0;

    if (new_pid == -1)
        return 1;
    if (new_pid > 0) {
        waitpid(new_pid, &status, 0);
        return display_error(status, NULL);
    }
    if (new_pid == 0)
        handle_duplicate_processus(path_with_function, current, env);
    return 1;
}

/**
 * @brief Check if the command exists in specified directories.
 *
 * This function iterates through directories in the PATH environment variable,
 * searching for the specified command, and returns the path if found.
 *
 * @param dir Pointer to the current directory to check.
 * @param path String containing directories from PATH variable.
 * @param tab Array of arguments containing the command name.
 * @param check Temporary buffer for constructing command paths.
 * @return Returns the full path of the command if found, or NULL otherwise.
 */
char *check_dir(char *dir, char *path, char **tab, char *check)
{
    while (dir != NULL) {
        check = malloc(strlen(dir) + strlen(tab[0]) + 2);
        if (check == NULL) {
            free(path);
            return NULL;
        }
        strcpy(check, dir);
        strcat(check, "/");
        strcat(check, tab[0]);
        if (access(check, F_OK) == 0) {
            free(path);
            return check;
        }
        dir = strtok(NULL, ":");
        free(check);
    }
    free(path);
    return NULL;
}

/**
 * @brief Check if the command contains a slash.
 *
 * This function checks if the command contains a slash ('/'),
 * indicating that it is an absolute or relative path.
 *
 * @param str The command string to check.
 * @return Returns 1 if a slash is found, 0 otherwise.
 */
static int check_if_slash(char *str)
{
    while (*str) {
        if (*str == '/') {
            return 1;
        }
        str++;
    }
    return 0;
}

/**
 * @brief Find the PATH environment variable in the environment.
 *
 * This function searches for the PATH variable in the provided environment
 * array and returns its value. If not found, it returns a default path.
 *
 * @param env Array of environment variables.
 * @param path Pointer to store the found path.
 * @return Returns the found path or a default path if not found.
 */
static char *find_path_env(char **env, char *path)
{
    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], "PATH=", 5) == 0) {
            path = strdup(env[i] + 5);
            return path;
        }
    }
    return strdup("/bin:/usr/bin:/usr/local/bin");
}

/**
 * @brief Get the full path of a command.
 *
 * This function returns the full path of a command using the PATH environment
 * variable, or returns the command itself if it is directly accessible.
 *
 * @param tab Array of arguments containing the command name.
 * @param env Array of environment variables.
 * @return Returns the full path of the command if found, or NULL otherwise.
 */
char *getpath(char **tab, char **env)
{
    char *path = NULL;
    char *check = NULL;
    char *dir = NULL;

    if (access(tab[0], F_OK) == 0)
        return strdup(tab[0]);
    if (check_if_slash(tab[0]) == 1)
        return NULL;
    path = find_path_env(env, path);
    dir = strtok(path, ":");
    check = check_dir(dir, path, tab, check);
    if (check == NULL)
        return NULL;
    return check;
}

/**
 * @brief Execute a command and handle its errors.
 *
 * This function retrieves the command path, forks a new process to execute it,
 * and handles errors such as command not found or execution failure.
 *
 * @param shell Pointer to the shell structure.
 * @param env Pointer to the linked list of environment variables.
 * @param current Pointer to the current command structure.
 * @return Returns 0 on success, or 1 on failure.
 */
int execute_command(shell_t *shell, env_t **env, command_t *current)
{
    char **env_tab = from_list_to_array(env);
    char *path = getpath(current->args, env_tab);

    if (path) {
        shell->return_value = split_fork(path, current, env_tab);
        free(path);
        free_array(env_tab);
        return 0;
    } else {
        if (path == NULL)
            dprintf(2, "%s: Command not found.\n", current->args[0]);
        shell->return_value = 1;
        free_array(env_tab);
        return 1;
    }
    free_array(env_tab);
    return 1;
}
