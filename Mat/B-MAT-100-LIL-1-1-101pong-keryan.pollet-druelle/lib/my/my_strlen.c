/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** compte la pluie
*/

int my_strlen(char const *str)
{
    char const *a = str;
    int co = 0;

    while (*a != '\0') {
        co = co + 1;
        a = a + 1;
    }
    return co;
}
