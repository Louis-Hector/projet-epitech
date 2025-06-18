/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** j aime la vie
*/

#include <stdbool.h>
#include "my.h"
#include <stdio.h>

int limits(int signe)
{
    if (signe == 1) {
        return 2147483647;
    } else {
        return -2147483647;
    }
}

int my_getnbr(char const *str)
{
    int result = 0;
    int signe = 1;
    int i = 0;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-') {
            signe *= -1;
        }
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        if (result > (2147483647 - (str[i] - '0')) / 10) {
            return limits(signe);
        }
        result = (result * 10) + (str[i] - '0');
        i++;
    }
    return result * signe;
}
