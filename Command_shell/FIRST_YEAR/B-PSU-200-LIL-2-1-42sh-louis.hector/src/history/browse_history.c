/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** browse_history.c
*/

#include "shell.h"

/**
 * @brief Search for a command in the history based on its index.
 *
 * This function traverses the history linked list to find the command
 * associated with the given index.
 *
 * @param index The index of the command to search for.
 * @param shell A pointer to the shell structure containing the history.
 * @return A pointer to the command string if found, NULL otherwise.
 */
char *search_asked_command(int index, shell_t *shell)
{
    history_t *current = shell->history;

    while (current) {
        if (current->index == index) {
            return current->command;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Configure the terminal to disable canonical mode and echo.
 *
 * This function modifies the terminal settings to disable canonical mode
 * and echo, allowing character-by-character input.
 *
 * @param old A pointer to a termios structure to save the current settings.
 */
void config_termios(struct termios *old)
{
    struct termios new;

    tcgetattr(STDIN_FILENO, old);
    new = *old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

/**
 * @brief Get the size of the history linked list.
 *
 * This function counts the number of nodes in the history linked list.
 *
 * @param size A pointer to an integer to store the size of the history.
 * @param shell A pointer to the shell structure containing the history.
 */
static void get_history_size(int *size, shell_t *shell)
{
    history_t *current = shell->history;

    while (current) {
        (*size)++;
        current = current->next;
    }
}

/**
 * @brief Retrieve a command from the history and display it.
 *
 * This function retrieves a command from the history based on the direction
 * specified in the terminal interaction structure and updates the terminal
 * display with the command.
 *
 * @param shell A pointer to the shell structure containing the history.
 * @param buffer A pointer to the buffer to store the retrieved command.
 * @param term A pointer to the terminal interaction structure.
 */
void recup_history_command(shell_t *shell,
    char *buffer, interaction_termios_t *term)
{
    char *hist_cmd = NULL;

    if (term->direction != 0) {
        term->index += term->direction;
        if (term->index < 0)
            term->index = 0;
        if (term->index > term->nb_line - 1)
            term->index = term->nb_line - 1;
        hist_cmd = search_asked_command(term->index, shell);
        if (hist_cmd) {
            term->pos = strlen(hist_cmd);
            strncpy(buffer, hist_cmd, term->pos);
            buffer[term->pos] = '\0';
            printf("\r\33[2K" GREEN "-> " CYAN "%s" RESET " %s",
                shell->prompt, buffer);
            fflush(stdout);
        }
        term->direction = 0;
    }
}

/**
 * @brief Initialize terminal settings for history browsing.
 *
 * This function initializes the terminal interaction structure and modifies
 * the terminal settings for browsing the history.
 *
 * @param term A pointer to the terminal interaction structure.
 * @param shell A pointer to the shell structure containing the history.
 */
void start_termios(interaction_termios_t *term, shell_t *shell)
{
    get_history_size(&term->nb_line, shell);
    term->index = term->nb_line;
    term->direction = 0;
    config_termios(&term->old);
    fflush(stdout);
    return;
}

/**
 * @brief Browse and interact with the shell history.
 *
 * This function provides an interactive interface to browse the shell
 * history, allowing the user to navigate and select commands.
 *
 * @param shell A pointer to the shell structure containing the history.
 * @return 0 on success.
 */
int browse_history(shell_t *shell)
{
    interaction_termios_t term = {0};
    char buffer[1024] = {0};
    char ch = 0;
    ssize_t input = 0;

    start_termios(&term, shell);
    while (1) {
        input = read(STDIN_FILENO, &ch, 1);
        if (input <= 0)
            continue;
        check_escape(ch, &term);
        delete_command_line(ch, &term, buffer, shell);
        if (verif_enter(ch, buffer, term, shell) == 1)
            break;
        write_in_terminal(ch, buffer, &term, shell);
        recup_history_command(shell, buffer, &term);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &term.old);
    return 0;
}
