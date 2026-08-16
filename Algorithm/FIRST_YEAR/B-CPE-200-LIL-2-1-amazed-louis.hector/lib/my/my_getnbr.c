/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** j aime la vie
*/

#include "my.h"

static int my_sign(char const *str, int i, int neg)
{
    if (i > 0 && str[i - 1] == '-') {
        neg = -1;
    } else {
        neg = 1;
    }
    return neg;
}

static int chara(char const *str)
{
    int i = 0;

    while (str[i] < 48 || str[i] > 57) {
        if (str[i] != '-' && str[i] != '+') {
            return 1;
        }
        i++;
    }
    return 0;
}

static int to_num(char const *str)
{
    int i;

    i = 0;
    while (str[i] < 48 || str[i] > 57) {
        i++;
    }
    return i;
}

static long numb(char const *str, int i, long number)
{
    while (str[i] >= 48 && str[i] <= 57){
        number *= 10;
        number += str[i] -48;
        i++;
    }
    return number;
}

int my_getnbr(char const *str)
{
    int i = 0;
    long number = 0;
    int neg = 1;
    int nb = 0;

    if (chara(str))
        return -1;
    i = to_num(str);
    neg = my_sign(str, i, neg);
    number = numb(str, i, number);
    number *= neg;
    if (number > 2147483647 || number < -2147483648) {
        return -1;
    }
    nb = number;
    return nb;
}
