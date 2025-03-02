/*
** EPITECH PROJECT, 2024
** read_script.c
** File description:
** read the script given
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/mysprite.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../include/my.h"


static void affect_plane(airplane_t *airplane, char **tab, int a)
{
    airplane[a].rectangle = sfRectangleShape_create();
    airplane[a].start.x = my_getnbr(tab[1]);
    airplane[a].start.y = my_getnbr(tab[2]);
    airplane[a].destination.x = my_getnbr(tab[3]);
    airplane[a].destination.y = my_getnbr(tab[4]);
    airplane[a].speed = my_getnbr(tab[5]);
    airplane[a].delay = my_getnbr(tab[6]);
    a++;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

static void init_tower(tower_t *tower, char **tab, int b)
{
    tower[b].circle = sfCircleShape_create();
    tower[b].position.x = my_getnbr(tab[1]);
    tower[b].position.y = my_getnbr(tab[2]);
    tower[b].radius = my_getnbr(tab[3]);
}

int allocate_memory(airplane_t **airplane, tower_t **tower
    , number_elements_t *number)
{
    *airplane = malloc(number->number_plane * sizeof(airplane_t));
    *tower = malloc(number->nb_tower * sizeof(tower_t));
    if (*airplane == NULL || *tower == NULL)
        return 84;
    return 0;
}

void count_elements(FILE *fp, number_elements_t *number)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, fp);
    while (read != -1) {
        if (line[0] == 'A')
            number->number_plane++;
        if (line[0] == 'T')
            number->nb_tower++;
        read = getline(&line, &len, fp);
    }
    free(line);
}

void read_airplanes_and_towers(FILE *fp, airplane_t *airplane
    , tower_t *tower, number_elements_t *number)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int a = 0;
    int b = 0;
    char **tab;

    read = getline(&line, &len, fp);
    while (read != -1) {
        tab = my_str_to_word_array(line);
        if (line[0] == 'A') {
            affect_plane(airplane, tab, a);
            a++;
        }
        if (line[0] == 'T') {
            init_tower(tower, tab, b);
            b++;
        }
        read = getline(&line, &len, fp);
    }
}

static int my_isdigit(char c)
{
    if (c > '9' || c < '0')
        return 0;
    return 1;
}

static int follow_loop(char *line)
{
    char **tab;
    int count = 0;

    tab = my_str_to_word_array(line);
    for (int j = 0; tab[j] != NULL; j++)
        count++;
    if (line[0] == 'A' && count != 7)
        return 84;
    if (line[0] == 'T' && count != 4)
        return 84;
    for (int i = 0; line[i] != '\n'; i++) {
        if (my_isdigit(line[i] == 0) && line[i] != ' '
            && line[i] != '\0' && line[i] != '.' && line[i] == '-')
            return 84;
    }
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
    return 0;
}

int check_error_handling(int ac, char **av)
{
    FILE *fd = fopen(av[1], "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fd == NULL)
        return 84;
    read = getline(&line, &len, fd);
    while (read != -1) {
        if (line == NULL)
            return 84;
        if (line[0] != 'A' && line[0] != 'T')
            return 84;
        if (follow_loop(line) == 84)
            return 84;
        read = getline(&line, &len, fd);
    }
    fclose(fd);
    return 0;
}

int read_script(char **av, airplane_t **airplane, tower_t **tower
    , number_elements_t *number)
{
    FILE *fp = fopen(av[1], "r");

    if (fp == NULL)
        return 84;
    count_elements(fp, number);
    if (allocate_memory(airplane, tower, number) == 84)
        return 84;
    fp = fopen(av[1], "r");
    read_airplanes_and_towers(fp, *airplane, *tower, number);
    return 0;
}
