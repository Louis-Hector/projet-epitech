/*
** EPITECH PROJECT, 2025
** 42SH
** File description:
** create the history and alias files
*/

#include "shell.h"

/**
 * @brief Construct the full path to a file in the user's home directory.
 *
 * This function retrieves the home of the user and appends the
 * provided filename to construct the full file path.
 *
 * @param filename Name of the file to append to the home directory path.
 * @return Returns the full path as a dynamically allocated string, or NULL
 *         if the 'HOME' variable or filename is not provided, or if memory
 *         allocation fails.
 */
char *get_home_user(char *filename)
{
    struct passwd *pw = getpwuid(getuid());
    char *home = NULL;
    int len = 0;
    char *full_path = NULL;

    if (!pw || !pw->pw_dir || !filename)
        return NULL;
    home = pw->pw_dir;
    len = strlen(home) + strlen(filename) + 1;
    full_path = malloc(len);
    if (!full_path)
        return NULL;
    strcpy(full_path, home);
    strcat(full_path, filename);
    return full_path;
}

int init_easter_egg(shell_t *shell_arg)
{
    memset(shell_arg->file, 0, sizeof(easter_egg_t));
    shell_arg->file->dragon = fopen("src/easter_egg/dragon.txt", "r");
    shell_arg->file->credits = fopen("src/easter_egg/credits.txt", "r");
    shell_arg->file->epitech = fopen("src/easter_egg/epitech.txt", "r");
    if (!shell_arg->file->dragon || !shell_arg->file->credits
        || !shell_arg->file->epitech)
        return 1;
    return 0;
}

/**
 * @brief Create or open a file with specific permissions.
 *
 * This function creates a file at the given path or opens it in append mode
 * with read/write permissions. If file creation fails, it outputs an error
 * message.
 *
 * @param history_path Path to the file to create or open.
 * @return Returns 0 on success, or 84 if file creation or opening fails.
 */
int create_files(shell_t *shell_arg)
{
    int fd = open(shell_arg->history_path, O_CREAT | O_RDWR | O_APPEND, 0600);

    shell_arg->prompt = strdup("$>");
    if (fd == -1) {
        dprintf(2, "Error: %s\n", strerror(errno));
        return 84;
    }
    shell_arg->file = malloc(sizeof(easter_egg_t));
    if (!shell_arg->file)
        return 84;
    init_easter_egg(shell_arg);
    close(fd);
    return 0;
}
