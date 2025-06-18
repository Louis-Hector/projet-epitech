/*
** EPITECH PROJECT, 2024
** mini_printf.c
** File description:
** Fonction who print a mini_printf
*/

#include "my.h"
#include <stdarg.h>
#include <stdio.h>

static void condition_s_c(const char *format, int *i, int *total_character
    , va_list list)
{
    char *s;
    char c;

    if (format[*i] == '%' && format[*i + 1] == 's') {
        s = va_arg(list, char *);
        my_putstr(s);
        *total_character += my_strlen(s);
        *i += 2;
    } else if (format[*i] == '%' && format[*i + 1] == 'c') {
        c = (char)va_arg(list, int);
        my_putchar(c);
        (*total_character)++;
        *i += 2;
    }
}

static int count_nbr(int nb)
{
    int count = 0;

    if (nb < 0) {
        nb = -nb;
    }
    do {
        count++;
        nb = nb / 10;
    } while (nb != 0);
    return count;
}

static void condition_d_i(const char *format, int *i, int *total_character
    , va_list list)
{
    int nb;

    if (format[*i] == '%' && (format[*i + 1] == 'i'
        || format[*i + 1] == 'd')) {
        nb = va_arg(list, int);
        my_put_nbr(nb);
        *total_character += count_nbr(nb);
        *i += 2;
    }
}

static void condition_modulo(const char *format, int *i, int *total_character)
{
    if (format[*i] == '%' && format[*i + 1] == '%') {
        my_putchar('%');
        (*total_character)++;
        (*i)++;
        }
}

int mini_printf(const char *format, ...)
{
    int total_character = 0;
    va_list list;
    int i = 0;

    va_start(list, format);
    for (; format[i] != '\0'; i++) {
        condition_s_c(format, &i, &total_character, list);
        condition_d_i(format, &i, &total_character, list);
        condition_modulo(format, &i, &total_character);
        if (format[i] == 0)
            break;
        if (format[i] != '%') {
            my_putchar(format[i]);
            total_character++;
        }
    }
    va_end(list);
    return total_character;
}
