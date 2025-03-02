/*
** EPITECH PROJECT, 2024
** cipher.c
** File description:
** encryptage and decryptage
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


static void make_condition(int **matrice, int i, int j, int n)
{
    if (n == 2 && j == 1 || n == 3 && j == 2)
        printf("%d", matrice[i][j]);
    else
        printf("%d   ", matrice[i][j]);
}

void printf_matrice(int **matrice, int n)
{
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            make_condition(matrice, i, j, n);
        printf("\n");
    }
}

int **create_matrix_from_string(const char *str, int n) 
{
    int **matrice = malloc(sizeof(int *) * n);
    int num = 0;
    
    for (int i = 0; i < n; i++)
        matrice[i] = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ( i*n+j < strlen(str))
                matrice[i][j] = (int) str[i * n + j];
            else
                matrice[i][j] = 0;
        }
    }
    printf_matrice(matrice, n);
    return matrice;
}

int main(int ac, char **av)
{
    create_matrix_from_string(av[1], 3);
}