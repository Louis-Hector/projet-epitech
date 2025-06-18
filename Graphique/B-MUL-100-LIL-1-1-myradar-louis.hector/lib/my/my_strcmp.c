/*
** EPITECH PROJECT, 2024
** strcmp
** File description:
** new
*/

#include <stdio.h>
#include "my.h"

int my_strcmp(const char *s1, const char *s2)
{
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);
    int i = 0;
    int j = my_strlen(s1);

    if (len1 > len2)
        j = len1;
    if (len1 < len2)
        j = len2;
    for (i; i < j; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }
    return 0;
}
