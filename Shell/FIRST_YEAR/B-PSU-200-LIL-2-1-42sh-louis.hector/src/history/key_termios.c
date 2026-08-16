/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** key_termios.c
*/

#include "shell.h"

/**
 * @brief Adjust the direction of terminal interaction based on arrow keys.
 *
 * This function interprets the arrow key to update the direction
 * for navigating through the terminal's history or other interactive actions.
 *
 * @param seq A character array containing the arrow key.
 * @param term A pointer to the terminal interaction structure to update.
 */
static void recover_top_or_down(char seq[2], interaction_termios_t *term)
{
    if (seq[0] == '[' && seq[1] == 'A') {
        term->direction -= 1;
        return;
    }
    if (seq[0] == '[' && seq[1] == 'B') {
        term->direction += 1;
        return;
    }
}

/**
 * @brief Check if an escape character is entered and handle it.
 *
 * This function detects an escape character (ASCII 27) and processes
 * additional input to determine the corresponding action.
 *
 * @param ch The character entered by the user.
 * @param term A pointer to the terminal interaction structure to update.
 */
void check_escape(char ch, interaction_termios_t *term)
{
    char seq[2];

    if (ch == 27) {
        if (read(STDIN_FILENO, seq, 2) == 2) {
            recover_top_or_down(seq, term);
        }
    }
    return;
}

/**
 * @brief Delete the last character from the command line buffer.
 *
 * This function removes the last character from the input buffer and
 * updates the display to reflect the current state of the buffer.
 *
 * @param ch The character entered by the user.
 * @param term A pointer to the terminal interaction structure.
 * @param buffer The buffer storing the current command line input.
 */
void delete_command_line(char ch, interaction_termios_t *term,
    char *buffer, shell_t *shell)
{
    if (ch == 127 || ch == 8) {
        if (term->pos > 0) {
            term->pos--;
            buffer[term->pos] = '\0';
            printf("\r\33[2K" GREEN "-> "CYAN "%s" RESET " %s",
                shell->prompt, buffer);
            fflush(stdout);
        }
    }
    return;
}

/**
 * @brief Write a character to the terminal and update the buffer.
 *
 * This function adds a non-special character to the input buffer
 * and displays the updated command line in the terminal.
 *
 * @param ch The character entered by the user.
 * @param buffer The buffer storing the current command line input.
 * @param term A pointer to the terminal interaction structure.
 */
void write_in_terminal(char ch, char *buffer,
    interaction_termios_t *term, shell_t *shell)
{
    if (check_for_tab(ch, buffer, term, shell) == 1)
        return;
    if (ch != '\n' && ch != 127 && ch != 8 && ch != 27) {
        buffer[term->pos] = ch;
        term->pos++;
        buffer[term->pos] = '\0';
        printf("\r\33[2K" GREEN "-> " CYAN "%s" RESET " %s",
            shell->prompt, buffer);
        fflush(stdout);
    }
    return;
}

/**
 * @brief Verify if the Enter key is pressed and handle the command.
 *
 * This function checks if the Enter key is pressed, processes the input
 * command, and restores the terminal settings upon confirmation.
 *
 * @param ch The character entered by the user.
 * @param buffer The buffer storing the current command line input.
 * @param term The terminal interaction structure.
 * @param shell A pointer to the shell structure to update with the command.
 * @return 1 if the Enter key is pressed and the process is complete, else 0.
 */
int verif_enter(char ch, char *buffer
    , interaction_termios_t term, shell_t *shell)
{
    if (ch == '\n') {
        buffer[term.pos] = '\0';
        printf("\n");
        tcsetattr(STDIN_FILENO, TCSANOW, &term.old);
        shell->command = strdup(buffer);
        return 1;
    }
    return 0;
}
