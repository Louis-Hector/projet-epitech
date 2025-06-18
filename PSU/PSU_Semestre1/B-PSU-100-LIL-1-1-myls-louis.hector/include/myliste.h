/*
** EPITECH PROJECT, 2024
** list for the flags fonctions
** File description:
** r t l d ...
*/


#ifndef MYLI_H_
    #define MYLI_H_

    #include "my.h"
    #include <stdlib.h>

typedef struct struct_liste {
    char flags;
    int (*function)(char const *);
} tab_t;

const tab_t list[] = {
    {'a', display_a},
    {'d', display_d},
    {'l', display_l},
    {'R', display_rmaj},
    {'r', display_r},
    {0, NULL}
};

#endif
