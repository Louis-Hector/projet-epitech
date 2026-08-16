/*
** EPITECH PROJECT, 2024
** my_str_isnum
** File description:
** Write a function that returns 1 if the string passed as parameter
*/

int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if ((str[i] > '9' || str[i] < '0')) {
            return 0;
        }
        i++;
    }
    return 1;
}
