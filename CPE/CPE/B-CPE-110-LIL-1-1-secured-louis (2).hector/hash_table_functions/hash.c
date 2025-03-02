/*
** EPITECH PROJECT, 2025
** hash
** File description:
** hash data
*/

#include "../libshell/hashtable.h"
#include <string.h>

int hash(char *key, __attribute__((unused)) int len)
{
    int hash = 0;

    for (int i = 0; key[i] != '\0'; i++)
        hash = key[i] + (hash << 6) + (hash << 16) - hash;
    if (hash < 0)
        hash = hash * -1;
    return hash;
}
