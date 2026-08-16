/*
** EPITECH PROJECT, 2024
** my_str
** File description:
** premiere occurence
*/

#include <stddef.h>
#include "my.h"

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int j = 0;
    int len_find = my_strlen(to_find);
    int len_str = my_strlen(str);
    int up_len = 0;

    if (len_find == 0) {
        return str;
    }
    for (i = 0; i <= (len_str - len_find); i++) {
        j = 0;
        while (j < len_find && str[i + j] == to_find[j])
            j++;
        if (j == len_find) {
            return &str[i];
        }
    }
    return NULL;
}
