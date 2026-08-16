/*
** EPITECH PROJECT, 2025
** my_str_cote
** File description:
** Write a function that splits a string into words with cote
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>
#include <stdlib.h>

void count_chars_inside_quotes(int *count, char const *str, int i)
{
    while (str[i] != '"' && str[i] != '\0') {
        (*count)++;
        i++;
    }
}

void count_characters(char const *str, int *count)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '"') {
            i++;
            count_chars_inside_quotes(count, str, i);
        }
    }
}

void extract_quotes(char *result, int *a, int *i, char const *str)
{
    while (str[*i] != '"' && str[*i] != '\0') {
        result[*a] = str[*i];
        (*a)++;
        (*i)++;
    }
}

char *my_str_quotes(char const *str)
{
    int length = 0;
    int a = 0;
    char *result = NULL;

    count_characters(str, &length);
    result = malloc(sizeof(char) * (length + 1));
    if (result == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '"') {
            i++;
            extract_quotes(result, &a, &i, str);
            break;
        }
    }
    result[a] = '\0';
    return result;
}
