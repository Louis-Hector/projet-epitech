/*
** EPITECH PROJECT, 2024
** mt_strn
** File description:
** Write a function that copies n characters from a string into another.
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (i < n && src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    if (i < n){
        dest[i] = '\0';
        i++;
    }
    return dest;
}
