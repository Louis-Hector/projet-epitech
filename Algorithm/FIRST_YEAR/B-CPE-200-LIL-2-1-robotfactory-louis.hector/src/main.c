/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** yolotron-asm
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "op.h"
#include "op_c.h"

char *assign_label_value(char *result_str)
{
    char *new_label = NULL;

    new_label = malloc(sizeof(char) * (2 + my_strlen(result_str)));
    new_label = my_strcpy(new_label, "%");
    new_label = my_strcat(new_label, result_str);
}

int find_if_label(char **command)
{
    int len = my_strlen(command[0]) - 1;

    if (command[0][len] == ':')
        return 1;
    return 0;
}

int find_what_cmd(char **command, op_t *info_command, int *label)
{
    int count = 0;

    if (find_if_label(command))
        *label = 1;
    for (int i = 0; op_tab[i].mnemonique != 0; i++) {
        if (command[*label]
            && my_strcmp(command[*label], op_tab[i].mnemonique) == 0) {
            info_command->mnemonique = op_tab[i].mnemonique;
            info_command->nbr_args = op_tab[i].nbr_args;
            info_command->code = op_tab[i].code;
            info_command->nbr_cycles = op_tab[i].nbr_cycles;
            info_command->comment = op_tab[i].comment;
        }
    }
    for (int i = *label + 1; command[i] != NULL; i++)
        count++;
    if (count != info_command->nbr_args)
        return 84;
    return 0;
}

static int print_help(void)
{
    mini_printf("USAGE\n");
    mini_printf("./asm file_name[.s]\n");
    mini_printf("DESCRIPTION\n");
    mini_printf("file_name file in assembly language to be converted "
        "into file_name.cor, an executable in\nthe Virtual Machine.\n");
    return 0;
}

static FILE *file_converted(char *file, FILE *file_cor)
{
    char *name = my_strdup(my_strtok(file, '.'));
    char *end_file = my_strdup(my_strtok(NULL, '\n'));
    char *file_name = malloc(sizeof(char) * my_strlen(name) + 5);

    if (name == NULL || end_file == NULL || file_name == NULL
        || my_strcmp(end_file, "s") != 0) {
        free(name);
        free(end_file);
        free(file_name);
        return NULL;
    }
    file_name = my_strcpy(file_name, name);
    file_name = my_strcat(file_name, ".cor");
    file_cor = fopen(file_name, "wb");
    free(name);
    free(end_file);
    free(file_name);
    return file_cor;
}

static int check_is_body(char **input, int *is_header, int *is_body)
{
    if (input[0] == NULL) {
        if (is_header)
            *is_body = 1;
        return 1;
    }
    *is_header = 1;
    return 0;
}

static int sup_main(char *line, instruction_t **head
    , header_t *header, label_t **labels)
{
    char **input = NULL;
    label_t *head_labels = *labels;
    static int is_header = 0;
    static int is_body = 0;
    static int position = 0;

    format_line(line);
    input = my_str_to_word_array(line);
    if (check_is_body(input, &is_header, &is_body) == 1)
        return 0;
    if (is_body == 0 && check_header(input, line) == 84)
        return 84;
    if (is_body) {
        if (find_body_info(input, head, position, labels) == 84)
            return 84;
        position = count_bytes(head);
    }
    if (add_header_infos(line, input, header) == 84)
        return 84;
    return 0;
}

static void write_and_clean(instruction_t **head, header_t *header
    , char *line, char *name)
{
    instruction_t *current = *head;
    FILE *file_cor = file_converted(my_strrchr(name, '/'), file_cor);
    int count = 0;

    reverse_bytes(&header->magic, 4);
    while (current != NULL) {
        if (current->code != 1 && current->code != 9 && current->code != 12
            && current->code != 15)
            count += 1;
        count_params(current, &count);
        count++;
        current = current->next;
    }
    header->prog_size = count;
    reverse_bytes(&header->prog_size, 4);
    fwrite(header, sizeof(header_t), 1, file_cor);
    write_body(file_cor, *head);
    free(line);
    free(header);
    fclose(file_cor);
}

static int continue_launch(int ac, char **av, label_t **labels)
{
    if (ac == 1 || av[1] == NULL)
        return 84;
    if (my_strcmp(av[1], "-h") == 0)
        return print_help();
    if (extract_labels(av[1], labels) == 84)
        return 84;
    return 1;
}

int main(int ac, char **av)
{
    FILE *file = fopen(av[1], "r");
    char *line = NULL;
    instruction_t *head = {0};
    size_t len = 0;
    header_t *header = malloc(sizeof(header_t));
    label_t *labels = NULL;
    int value = continue_launch(ac, av, &labels);

    if (value == 0 || value == 84)
        return value;
    if (file == NULL)
        return 84;
    while (getline(&line, &len, file) != -1)
        if (sup_main(line, &head, header, &labels) == 84)
            return 84;
    write_and_clean(&head, header, line, av[1]);
    fclose(file);
    return 0;
}
