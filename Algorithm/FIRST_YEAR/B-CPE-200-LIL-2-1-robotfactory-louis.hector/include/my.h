/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h
*/

#ifndef MY
    #define MY

    #include <unistd.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <stdint.h>
    #include "op.h"

typedef struct label_s {
    char *name;
    int position;
    struct label_s *next;
} label_t;

typedef struct instruction_s {
    char code;
    unsigned char coding_byte;
    int size;
    char *params[MAX_ARGS_NUMBER];
    int param_type;
    struct instruction_s *next;
} instruction_t;

void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
void dos_boucle(int *array, int size, int iteration);
int count_word(char const *str);
void count_char(char const *str, int *i, char **tab, int word);
char **my_str_to_word_array(char const *str);
char *my_strdup(char const *src);
int my_show_word_array(char *const *tab);
int limits(int signe);
void verification_max(void);
int mini_printf(const char *format, ...);
int display_a(char const *str);
int display_d(char const *str);
int display_l(char const *str);
int display_rmaj(char const *str);
int display_r(char const *str);
int search_square(char **map, int height, int width);
char **generate_tab_empty(char *str, int nb);
int verif_point(char **av);
char *my_strtok(char *str, const char delim);
int find_what_cmd(char **command, op_t *info_command, int *label);
void print_body_info(instruction_t *head);
int find_body_info(char **input, instruction_t **head
    , int position, label_t **labels);
char *my_strtok(char *str, const char delim);
int check_header(char **input, char *line);
char *my_str_quotes(char const *str);
int add_header_infos(char *line, char **input, header_t *header);
void write_body(FILE *file_cor, instruction_t *head);
char *check_comment(char *line);
void reverse_bytes(void *ptr, size_t size);
int extract_labels(const char *filename, label_t **labels);
void count_params(instruction_t *current, int *count);
void check_direct(instruction_t *current, int *count);
int count_bytes(instruction_t **head);
int check_type(op_t *info_command, char **params);
void add_instruction_to_list(instruction_t **head
    , op_t *info_command, char **params);
char *remove_comma_from_str(char *str);
int handle_label(char **args, label_t **labels, int position);
int process_label(char **args, label_t **labels, instruction_t **head);
int extract_labels(const char *filename, label_t **labels);
int add_label(label_t **head, char *name, int position);
int find_instrcution_info(char **input, instruction_t **head);
char *int_to_str(int nombre);
char *assign_label_value(char *result_str);
void format_line(char *line);
void free_tab(char **args);
char *my_strrchr(char *str, char c);

#endif
