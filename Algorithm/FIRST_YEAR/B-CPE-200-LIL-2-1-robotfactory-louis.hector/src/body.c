/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-louis.hector
** File description:
** body
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "op.h"

static unsigned char get_coding_byte(char **params)
{
    unsigned char coding_byte = 0;
    int shift = 6;

    for (int i = 0; params[i] != NULL; i++) {
        if (params[i][0] == 'r') {
            coding_byte |= (1 << shift);
            shift -= 2;
            continue;
        }
        if (params[i][0] == DIRECT_CHAR)
            coding_byte |= (2 << shift);
        else
            coding_byte |= (3 << shift);
        shift -= 2;
    }
    return coding_byte;
}

static int get_byte_size(char **params, char code)
{
    int byte_size = 0;
    int direct_size = 4;

    if (code == 9 || code == 10 || code == 11 || code == 12 || code == 15)
        direct_size = 2;
    for (int i = 0; params[i] != NULL; i++) {
        if (params[i][0] == 'r') {
            byte_size += 1;
            continue;
        }
        if (params[i][0] == DIRECT_CHAR)
            byte_size += direct_size;
        else
            byte_size += 2;
    }
    return byte_size;
}

void add_instruction_to_list(instruction_t **head
    , op_t *info_command, char **params)
{
    int i = 0;
    instruction_t *new_inst = malloc(sizeof(instruction_t));
    instruction_t *tmp = *head;

    if (!new_inst)
        return;
    new_inst->code = info_command->code;
    for (; i < info_command->nbr_args; i++)
        new_inst->params[i] = remove_comma_from_str(params[i]);
    new_inst->params[i] = NULL;
    new_inst->coding_byte = get_coding_byte(new_inst->params);
    new_inst->size = get_byte_size(new_inst->params, new_inst->code);
    new_inst->next = NULL;
    if (!*head)
        *head = new_inst;
    else {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_inst;
    }
}

int check_type(op_t *info_command, char **params)
{
    char param_type;

    for (int i = 0; i < op_tab[info_command->code - 1].nbr_args; i++) {
        param_type = params[i][0];
        if (param_type == 'r' && (my_getnbr(params[i] + 1) < 1
            || my_getnbr(params[i] + 1) > 16))
            return 84;
        if ((param_type == 'r'
            && !(op_tab[info_command->code - 1].type[i] & T_REG)))
            return 84;
        if (param_type == '%'
            && !(op_tab[info_command->code - 1].type[i] & T_DIR))
            return 84;
        if (param_type != 'r' && param_type != '%'
            && !(op_tab[info_command->code - 1].type[i] & T_IND))
            return 84;
    }
    return 0;
}

static int find_diff_label(char **param, int position
    , label_t **labels, int i)
{
    label_t *head = *labels;
    char *result_str = NULL;
    int result = 0;

    while (head) {
        if (my_strcmp(param[i] + 2, head->name) == 0)
            break;
        head = head->next;
    }
    if (head) {
        result = head->position - position;
        if (result < 0)
            result = 65535 + result + 1;
        result_str = int_to_str(result);
        param[i] = assign_label_value(result_str);
    } else
        return 84;
    return 0;
}

static int affect_value_to_label(char **param, int position, label_t **labels)
{
    int return_value = 0;

    for (int i = 1; param[i]; i++) {
        if (my_strncmp(param[i], "%:", 2) == 0) {
            param[i] = remove_comma_from_str(param[i]);
            return_value = find_diff_label(param, position, labels, i);
        }
        if (return_value == 84)
            return 84;
    }
    return 0;
}

int find_body_info(char **input, instruction_t **head
    , int position, label_t **labels)
{
    op_t info_command = {0};
    int label = 0;

    if (find_what_cmd(input, &info_command, &label) == 84)
        return 84;
    if (check_type(&info_command, &input[label + 1]) == 84)
        return 84;
    if (affect_value_to_label(input, position, labels) == 84)
        return 84;
    if (input[label + 1])
        add_instruction_to_list(head, &info_command, &input[label + 1]);
    return 0;
}

static void write_direct(int value, instruction_t *current, FILE *file_cor)
{
    if (current->code == 9 || current->code == 11
        || current->code == 12 || current->code == 15
        || current->code == 14 || current->code == 10) {
        reverse_bytes(&value, 2);
        fwrite(&value, 2, 1, file_cor);
    } else {
        reverse_bytes(&value, 4);
        fwrite(&value, sizeof(int), 1, file_cor);
    }
}

static void write_params(int value, instruction_t *current, FILE *file_cor)
{
    for (int i = 0; current->params[i] != NULL; i++) {
        if (current->params[i][0] == 'r') {
            value = my_getnbr(current->params[i] + 1);
            fwrite(&value, 1, 1, file_cor);
            continue;
        }
        if (current->params[i][0] == DIRECT_CHAR) {
            value = my_getnbr(current->params[i] + 1);
            write_direct(value, current, file_cor);
        } else {
            value = my_getnbr(current->params[i]);
            reverse_bytes(&value, 2);
            fwrite(&value, 2, 1, file_cor);
        }
    }
}

void write_body(FILE *file_cor, instruction_t *head)
{
    instruction_t *current = head;
    int value = 0;

    while (current) {
        fwrite(&current->code, sizeof(char), 1, file_cor);
        if (current->code != 1 && current->code != 9 && current->code != 12
            && current->code != 15)
            fwrite(&current->coding_byte, sizeof(unsigned char), 1, file_cor);
        write_params(value, current, file_cor);
        current = current->next;
    }
}
