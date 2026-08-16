/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** auto_complete.c
*/

#include "shell.h"

/**
 * @brief Check if the character is a tab key.
 *
 * This function checks if the given character is a tab key ('\t').
 *
 * @param ch The character to check.
 * @param buffer The input buffer.
 * @param term The terminal settings.
 * @param shell The shell structure.
 * @return 1 if the character is a tab key, 0 otherwise.
 */
int get_length_last_space(char *buffer)
{
    int i = 0;
    int last_space = 0;

    while (buffer[i] != '\0') {
        if (buffer[i] == ' ')
            last_space = i;
        i++;
    }
    if (last_space == 0)
        return 0;
    return last_space + 1;
}

/**
 * @brief Add the completed matches at the end of the buffer.
 *
 * This function appends the completed matches to the end of the buffer
 * and updates the terminal position.
 *
 * @param matches The completed matches.
 * @param buffer The input buffer.
 * @param term The terminal settings.
 */
static void add_complete_at_the_end(char *matches,
    char *buffer, interaction_termios_t *term)
{
    int i = 0;

    if (!matches)
        return;
    term->pos = get_length_last_space(buffer);
    for (i = 0; matches[i] != '\0'; i++)
        buffer[term->pos + i] = matches[i];
    buffer[term->pos + i] = '\0';
    term->pos += i;
}

/**
 * @brief Check if the matches are valid and update the buffer.
 *
 * This function checks if the matches are valid and updates the buffer
 * accordingly. If there is only one match, it appends it to the end of the
 * buffer. If there are multiple matches, it prints them.
 *
 * @param matches The completed matches.
 * @param buffer The input buffer.
 * @param term The terminal settings.
 * @param shell The shell structure.
 */
static void check_for_auto_change(char *matches,
    char *buffer, interaction_termios_t *term, shell_t *shell)
{
    char *many_matche = NULL;

    if (!matches)
        return;
    many_matche = strrchr(matches, ' ');
    if (many_matche == NULL)
        add_complete_at_the_end(matches, buffer, term);
    else
        printf("\n%s\n", matches);
    printf("\r\33[2K" GREEN "-> " CYAN "%s" RESET " %s",
    shell->prompt, buffer);
    fflush(stdout);
    term->pos = strlen(buffer);
}

/**
 * @brief Create a glob pattern from the last word in the buffer.
 *
 * This function creates a glob pattern by appending '*' to the last word
 * in the buffer. If there is no space in the buffer, it uses the entire
 * buffer as the last word.
 *
 * @param buffer The input buffer.
 * @return The created glob pattern.
 */
static char *create_glob_pattern(char *buffer)
{
    char *last_word = strrchr(buffer, ' ');
    char *glob_pattern = NULL;

    if (last_word == NULL)
        last_word = buffer;
    else
        last_word++;
    glob_pattern = malloc(strlen(last_word) + 2);
    if (glob_pattern == NULL)
        return NULL;
    glob_pattern[0] = '\0';
    strcat(glob_pattern, last_word);
    strcat(glob_pattern, "*");
    return glob_pattern;
}

/**
 * @brief Check for auto-completion using globbing.
 *
 * This function checks for auto-completion by creating a glob pattern
 * and using it to find matches. If there are matches, it updates the
 * buffer and terminal position accordingly.
 *
 * @param buffer The input buffer.
 * @param term The terminal settings.
 * @param shell The shell structure.
 */
static void check_for_auto_complete(char *buffer,
    interaction_termios_t *term, shell_t *shell)
{
    char *glob_pattern = create_glob_pattern(buffer);
    char *matches = NULL;

    if (glob_pattern == NULL)
        return;
    term->pos = strlen(buffer);
    matches = change_globbins_in_line(glob_pattern);
    if (strcmp(matches, glob_pattern) == 0) {
        free(glob_pattern);
        free(matches);
        return;
    }
    check_for_auto_change(matches, buffer, term, shell);
    free(glob_pattern);
    free(matches);
}

/**
 * @brief Check if the character is a tab key and handle auto-completion.
 *
 * This function checks if the given character is a tab key ('\t').
 * If it is, it calls the auto-completion function.
 *
 * @param ch The character to check.
 * @param buffer The input buffer.
 * @param term The terminal settings.
 * @param shell The shell structure.
 * @return 1 if the character is a tab key, 0 otherwise.
 */
int check_for_tab(char ch, char *buffer,
    interaction_termios_t *term, shell_t *shell)
{
    if (ch == '\t') {
        check_for_auto_complete(buffer, term, shell);
        return 1;
    }
    return 0;
}
