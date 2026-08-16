/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** header
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../include/my.h"
#include "../include/op.h"

int add_header_infos(char *line, char **input, header_t *header)
{
    char *sentence;

    if (my_strcmp(input[0], ".name") == 0) {
        sentence = my_str_quotes(line);
        if (my_strlen(sentence) > PROG_NAME_LENGTH)
            return 84;
        my_strncpy(header->prog_name, sentence, PROG_NAME_LENGTH + 1);
        sentence = NULL;
    }
    if (my_strcmp(input[0], ".comment") == 0) {
        sentence = my_str_quotes(line);
        if (my_strlen(sentence) > COMMENT_LENGTH)
            return 84;
        my_strncpy(header->comment, sentence, COMMENT_LENGTH + 1);
    }
    header->magic = COREWAR_EXEC_MAGIC;
    header->prog_size = 0;
}
