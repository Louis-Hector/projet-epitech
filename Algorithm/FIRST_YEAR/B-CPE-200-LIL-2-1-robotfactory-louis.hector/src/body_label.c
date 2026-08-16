/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** body label
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "op.h"
#include "my.h"

char *remove_comma_from_str(char *str)
{
    char *new_str = my_strdup(str);
    int i = 0;

    while (new_str[i] != '\0')
        i++;
    if (new_str[i - 1] == ',')
        new_str[i - 1] = '\0';
    return new_str;
}

void reverse_bytes(void *ptr, size_t size)
{
    unsigned char *byte_ptr = (unsigned char *)ptr;
    unsigned char tmp = 0;
    size_t i = 0;

    for (; i < size / 2; i++) {
        tmp = byte_ptr[i];
        byte_ptr[i] = byte_ptr[size - 1 - i];
        byte_ptr[size - 1 - i] = tmp;
    }
}

int handle_label(char **args, label_t **labels, int position)
{
    int arg_len = 0;
    int return_value = 0;

    for (int i = 0; args[i]; i++) {
        arg_len = my_strlen(args[i]);
        if (arg_len > 1 && args[i][arg_len - 1] == ':')
            return_value = add_label(labels, args[i], position);
        if (return_value == 84)
            return 84;
    }
}

int process_label(char **args, label_t **labels, instruction_t **head)
{
    static int is_header = 0;
    static int is_body = 0;
    static int position = 0;

    if (!args[0]) {
        if (is_header)
            is_body = 1;
        return 0;
    }
    is_header = 1;
    if (is_body) {
        if (handle_label(args, labels, position) == 84)
            return 84;
        if (find_instrcution_info(args, head) == 84)
            return 84;
        position = count_bytes(head);
    }
}

int extract_labels(const char *filename, label_t **labels)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    char **args = NULL;
    size_t len = 0;
    instruction_t *head = {0};

    if (!file)
        return 84;
    while (getline(&line, &len, file) != -1) {
        format_line(line);
        args = my_str_to_word_array(line);
        if (process_label(args, labels, &head) == 84)
            return 84;
        free_tab(args);
    }
    free(line);
    fclose(file);
    return 0;
}
