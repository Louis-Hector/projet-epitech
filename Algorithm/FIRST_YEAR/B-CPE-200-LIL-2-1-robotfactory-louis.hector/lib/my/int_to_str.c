/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** int_to_str
*/

#include <stddef.h>
#include <stdlib.h>

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
