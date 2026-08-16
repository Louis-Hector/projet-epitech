/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** easter_egg
*/

#include "shell.h"

/**
 * @brief Get the ANSI color code based on the provided color flag.
 *
 * This function returns the corresponding ANSI color code for the given
 * color flag. If the flag is not recognized, an empty string is returned.
 *
 * @param color_flag The color flag (e.g., "-r", "-g", etc.).
 * @return The ANSI color code as a string.
 */
const char *get_ansi_color(const char *color_flag)
{
    if (color_flag == NULL)
        return "";
    if (strcmp(color_flag, "-r") == 0)
        return "\033[31m";
    if (strcmp(color_flag, "-g") == 0)
        return "\033[32m";
    if (strcmp(color_flag, "-b") == 0)
        return "\033[34m";
    if (strcmp(color_flag, "-y") == 0)
        return "\033[33m";
    if (strcmp(color_flag, "-m") == 0)
        return "\033[35m";
    if (strcmp(color_flag, "-c") == 0)
        return "\033[36m";
    if (strcmp(color_flag, "-w") == 0)
        return "\033[37m";
    if (strcmp(color_flag, "-n") == 0)
        return "\033[30m";
    return "";
}

/**
 * @brief Write the contents of a file to standard output with color.
 *
 * This function reads each line from the specified file and writes it
 * to standard output, applying the specified color formatting.
 *
 * @param file The file pointer to read from.
 * @param color The ANSI color code to apply.
 */
static void write_file(FILE *file, const char *color)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, file);
    while (read != -1) {
        write(1, color, strlen(color));
        write(1, line, read);
        write(1, "\033[0m", strlen("\033[0m"));
        read = getline(&line, &len, file);
    }
    rewind(file);
    free(line);
}

/**
 * @brief Display the contents of an Easter egg file based on the command.
 *
 * This function checks the command and displays the corresponding
 * Easter egg file (dragon, epitech, or credits) with color formatting.
 *
 * @param tab The command arguments.
 * @param env The environment variables.
 * @param old_path The old path for the shell.
 * @param shell The shell structure.
 * @return 0 on success, 1 on error.
 */
int display_easter_egg(char **tab,
    env_t **env, char **old_path, shell_t *shell)
{
    FILE *file = NULL;
    const char *color = get_ansi_color(tab[1]);

    if (strcmp(tab[0], "dragon") == 0)
        file = shell->file->dragon;
    if (strcmp(tab[0], "epitech") == 0)
        file = shell->file->epitech;
    if (strcmp(tab[0], "credits") == 0)
        file = shell->file->credits;
    if (!env || !file || !old_path)
        return 1;
    write_file(file, color);
    return 0;
}
