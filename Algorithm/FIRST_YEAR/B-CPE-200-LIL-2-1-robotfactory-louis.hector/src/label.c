/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** label
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "op.h"
#include "my.h"

static int parse_labels(label_t *temp, label_t **prev, label_t *new)
{
    while (temp) {
        if (my_strcmp(temp->name, new->name) == 0) {
            free(new->name);
            free(new);
            return 84;
        }
        *prev = temp;
        temp = temp->next;
    }
    return 0;
}

int add_label(label_t **head, char *name, int position)
{
    label_t *new = malloc(sizeof(label_t));
    label_t *temp = *head;
    label_t *prev = NULL;

    if (!new)
        return 84;
    new->name = my_strdup(name);
    new->name[my_strlen(new->name) - 1] = '\0';
    new->position = position;
    new->next = NULL;
    if (!*head) {
        *head = new;
        return 0;
    }
    if (parse_labels(temp, &prev, new) == 84)
        return 84;
    prev->next = new;
    return 0;
}

void check_direct(instruction_t *current, int *count)
{
    if (current->code == 9 || current->code == 11
        || current->code == 12 || current->code == 15
        || current->code == 14 || current->code == 10)
        *count += 2;
    else
        *count += 4;
}

void count_params(instruction_t *current, int *count)
{
    for (int i = 0; current->params[i] != NULL; i++) {
        if (current->params[i][0] == 'r') {
            *count += 1;
            continue;
        }
        if (current->params[i][0] == DIRECT_CHAR)
            check_direct(current, count);
        else
            *count += 2;
    }
}

int count_bytes(instruction_t **head)
{
    instruction_t *current = *head;
    int count = 0;

    while (current != NULL) {
        if (current->code != 1 && current->code != 9 && current->code != 12
            && current->code != 15)
            count += 1;
        count_params(current, &count);
        count++;
        current = current->next;
    }
    return count;
}

int find_instrcution_info(char **input, instruction_t **head)
{
    op_t info_command = {0};
    int label = 0;

    if (find_what_cmd(input, &info_command, &label) == 84)
        return 84;
    if (check_type(&info_command, &input[label + 1]) == 84)
        return 84;
    if (input[label + 1] != NULL)
        add_instruction_to_list(head, &info_command, &input[label + 1]);
    return 0;
}
