/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** the original printf function
*/

#include "my.h"
#include <stdarg.h>
#include <stdlib.h>

int flag_compatibility(char *values, char c)
{
    for (int i = 0; values[i] != '\0'; i++){
        if (values[i] == c)
            return 1;
    }
    return 0;
}

char *tag_modif(const char *format, int i, char spe)
{
    char *tag = malloc(2 * sizeof(char) + 1);
    int j = 0;

    while (format[i] != spe){
        if (format[i] == 'h' || format[i] == 'l'){
            tag[j] = format[i];
            j++;
        }
        i++;
    }
    tag[j] = '\0';
    return tag;
}

int flag_cond(const char *format, int *p, va_list args, int i)
{
    char values[19] = {'a', 'A', 'e', 'E', 'f', 'F', 'x',
        'X', 'g', 'G', 'd', 'i', 'u', 'o', 'n', 'p', '%', 's', 'c'};
    char spe;
    char *modifier;
    int temp = i;

    while (format[i] != '\0' && flag_compatibility(values, format[i]) == 0)
        i++;
    spe = format[i];
    if (spe == '\0')
        return i;
    modifier = tag_modif(format, temp, spe);
    flag(spe, p, args, modifier);
    return i;
}

int my_printf(const char *format, ...)
{
    va_list args;
    int i = 0;
    int len = 0;
    int *p = &len;

    va_start(args, format);
    while (format[i] != '\0'){
        if (format[i] == '%' && format[i + 1] != '\0'){
            i = flag_cond(format, p, args, i + 1);
        } else {
            my_putchar(format[i]);
            len++;
        }
        i++;
    }
    va_end(args);
    return len;
}
