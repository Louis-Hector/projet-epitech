/*
** EPITECH PROJECT, 2024
** print_time.c
** File description:
** create the time with all informations
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/mysprite.h"
#include <math.h>

char *count_number_malloc(char *chaine, int nombre)
{
    if (nombre == 0) {
        chaine = malloc(sizeof(char) * 2);
        chaine[0] = '0';
        chaine[1] = '\0';
        return chaine;
    }
    return NULL;
}

char *int_to_str(int nombre)
{
    int stack = 0;
    char *chaine;
    int i = 0;

    chaine = count_number_malloc(chaine, nombre);
    stack = nombre;
    while (stack > 0) {
        stack /= 10;
        i++;
    }
    chaine = malloc(sizeof(char) * (i + 1));
    chaine[i] = '\0';
    while (nombre > 0) {
        --i;
        chaine[i] = '0' + (nombre % 10);
        nombre /= 10;
    }
    return chaine;
}

void print_time(sfClock *clock, sfRenderWindow *window)
{
    sfTime time;
    int nombre = 0;
    char *chaine;
    sfFont *font = sfFont_createFromFile("arial/ArialCEMTBlack.ttf");
    sfText *text = sfText_create();

    sfText_setPosition(text, (sfVector2f){1800, 50});
    time = sfClock_getElapsedTime(clock);
    nombre = (int)time.microseconds / 1000000;
    chaine = int_to_str(nombre);
    sfText_setFont(text, font);
    sfText_setString(text, chaine);
    sfText_setCharacterSize(text, 60);
    sfRenderWindow_drawText(window, text, NULL);
    free(chaine);
    sfFont_destroy(font);
    sfText_destroy(text);
}
