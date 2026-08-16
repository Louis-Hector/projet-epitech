/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** file_history.c
*/

/**
 * @file file_history.c
 * @brief Functions for managing the history of commands in a shell.
 *
 * This file contains functions to handle the history of commands, including
 * adding commands to a linked list, saving/loading history from a file, and
 * formatting commands.
 */

#include "shell.h"

/**
 * @brief Get the current time in HH:MM format.
 *
 * This function retrieves the current local time and formats it
 * into a string in the format "HH:MM". The caller is responsible
 * for freeing the allocated memory for the returned string.
 *
 * @return A string containing the current time in HH:MM format.
 *         Returns NULL if memory allocation fails.
 */
char *get_time_of_command(void)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char *time_str = malloc(6);

    if (!time_str)
        return NULL;
    strftime(time_str, 6, "%H:%M", tm);
    return time_str;
}

/**
 * @brief Get the size of the history list.
 *
 * This function calculates the size of the history linked list.
 *
 * @param history A pointer to the head of the history linked list.
 * @return The size of the history list.
 */
int get_size_of_history_list(history_t **history)
{
    int size = 0;
    history_t *current = *history;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

/**
 * @brief Add a command to the history linked list.
 *
 * This function creates a new node for the history linked list
 * and adds it to the end of the list. The new node contains
 * the command, time, and index.
 *
 * @param history A pointer to the head of the history linked list.
 * @param command The command to be added to the history.
 * @param time The time when the command was executed.
 * @param index The index of the command in the history.
 *
 * @return 0 on success, 1 on failure.
 */
int add_command_to_list(history_t **history
    , char *command, char *time, int index)
{
    history_t *new_command = malloc(sizeof(history_t));
    history_t *current = NULL;

    if (!new_command || !time)
        return 1;
    new_command->command = strdup(command);
    new_command->time = strdup(time);
    new_command->index = index;
    new_command->next = NULL;
    if (*history == NULL) {
        *history = new_command;
    } else {
        current = *history;
        while (current->next != NULL)
            current = current->next;
        current->next = new_command;
    }
    return 0;
}

/**
 * @brief Format a command by appending a newline character.
 *
 * This function takes a command string and appends a newline character
 * to it. The caller is responsible for freeing the allocated memory.
 *
 * @param command The command to format.
 * @return A newly allocated string containing the formatted command.
 * Returns NULL if memory allocation fails.
 */
static char *format_command(char *command)
{
    char *formatted_command = malloc(strlen(command) + 1);

    if (!formatted_command)
        return NULL;
    strcpy(formatted_command, command);
    formatted_command[strlen(command)] = '\0';
    return formatted_command;
}

/**
 * @brief Convert a line from the history file to a history node.
 *
 * This function parses a line from the history file and creates a new
 * node in the history linked list.
 *
 * @param history A pointer to the head of the history linked list.
 * @param line The line to parse.
 * @return 0 on success, 1 on failure.
 */
static int from_line_to_node(history_t **history, char *line)
{
    char *index_str = strtok(line, " ");
    char *time = strtok(NULL, " ");
    char *command = strtok(NULL, "\n");
    char *command_with_nl = NULL;
    int index = 0;

    if (!index_str || !time || !command)
        return 1;
    index = atoi(index_str);
    command_with_nl = format_command(command);
    if (add_command_to_list(history, command_with_nl, time, index) == 1) {
        free(command_with_nl);
        return 1;
    }
    free(command_with_nl);
    return 0;
}

/**
 * @brief Load the history from a file into a linked list.
 *
 * This function reads the history file line by line and converts each
 * line into a node in the history linked list.
 *
 * @param history A pointer to the head of the history linked list.
 * @param history_path The path to the history file.
 * @return A pointer to the head of the history linked list on success,
 * NULL on failure.
 */
history_t *from_file_to_list(history_t **history, char *history_path)
{
    FILE *file = fopen(history_path, "r");
    char *line = NULL;
    size_t len = 0;

    if (file == NULL) {
        dprintf(2, "Error opening file\n");
        return NULL;
    }
    while (getline(&line, &len, file) != -1)
        if (from_line_to_node(history, line) == 1)
            continue;
    free(line);
    fclose(file);
    return *history;
}

/**
 * @brief Save the history linked list to a file.
 *
 * This function writes the history linked list to a file, with each
 * node written as a line in the file.
 *
 * @param history A pointer to the head of the history linked list.
 * @param history_path The path to the history file.
 * @return 0 on success, 84 on failure.
 */
int from_list_to_file(history_t **history, char *history_path)
{
    FILE *file = fopen(history_path, "w");
    history_t *current = *history;

    if (file == NULL)
        return 84;
    while (current != NULL) {
        fprintf(file, "%5d %s %s\n", current->index,
            current->time, current->command);
        current = current->next;
    }
    fclose(file);
    return 0;
}
