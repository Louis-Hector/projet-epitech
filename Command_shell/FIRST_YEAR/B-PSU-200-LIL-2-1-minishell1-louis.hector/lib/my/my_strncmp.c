/*
** EPITECH PROJECT, 2024
** my_strncmp.c
** File description:
** Same but  with n
*/

#include <stddef.h>
#include "my.h"
#include <stdio.h>

int my_strncmp(char const *s1, char const *s2, int n)
{
    if (s1 == NULL || s2 == NULL || n < 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }
    return 0;
}
