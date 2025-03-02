/*
** EPITECH PROJECT, 2024
** architect
** File description:
** make the code architec
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include <string.h>

double **mallocalisation(double **tab)
{
    for (int a = 0; a < 3; a++)
        tab[a] = malloc(sizeof(double) * 1);
    return tab;
}

static int chec_verif(char const *str)
{
    int i = 0;
    int count = 0;

    if (strcmp(str, "-") == 0)
        return 0;
    if (strcmp(str, "-t") == 0 || strcmp(str, "-z") == 0 ||
        strcmp(str, "-r") == 0 || strcmp(str, "-s") == 0)
        return 1;
    if (str[0] == '-')
        i++;
    while (str[i] != '\0') {
        if (str[i] == '.')
            count++;
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
            return 0;
        i++;
    }
    if (count > 1)
        return 0;
    return 1;
}

static void make_translation(char **av, int i, double *x, double *y)
{
    double h = atoi(av[i + 1]);
    double j = atoi(av[i + 2]);
    double **result = function_translation(x, y, h, j);

    *x = result[0][0];
    *y = result[1][0];
    i += 2;
}

static void make_scaling(char **av, int i, double *x, double *y)
{
    double m = atoi(av[i + 1]);
    double n = atoi(av[i + 2]);
    double **result = function_scaling(x, y, m, n);

    *x = result[0][0];
    *y = result[1][0];
    i += 2;
}

void make_rotation(char **av, int i, double *x, double *y)
{
    double d = atoi(av[i + 1]);
    double **result = function_rotation(x, y, d);

    *x = result[0][0];
    *y = result[1][0];
    i++;
}

void make_reflexion(char **av, int i, double *x, double *y)
{
    double d = atoi(av[i + 1]);
    double **result = function_reflexion(x, y, d);

    *x = result[0][0];
    *y = result[1][0];
    i++;
}

static void make_condition(double **matrice, int i, int j)
{
    if (matrice[i][j] < 0 && matrice[i][j] > -0.05)
        matrice[i][j] = 0.00;
    if (j == 2)
        printf("%.2f", matrice[i][j]);
    else
        printf("%.2f   ", matrice[i][j]);
}

void printf_matrice(double **matrice)
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            make_condition(matrice, i, j);
        printf("\n");
    }
}

static int fonction_condition(char **av, int ac)
{
    double x = atoi(av[1]);
    double y = atoi(av[2]);

    for (int i = 3; i < ac; i++) {
        if (test_condition(av, ac) == 84)
            return 84;
        if (strcmp(av[i], "-t") == 0 && (i + 2 < ac))
            make_translation(av, i, &x, &y);
        if (strcmp(av[i], "-z") == 0 && (i + 2 < ac))
            make_scaling(av, i, &x, &y);
        if (strcmp(av[i], "-r") == 0 && (i + 1 < ac))
            make_rotation(av, i, &x, &y);
        if (strcmp(av[i], "-s") == 0 && (i + 1 < ac))
            make_reflexion(av, i, &x, &y);
    }
    return 0;
}

int main(int ac, char **av)
{
    if (ac < 4) {
        exit(84);
    }
    for (int i = 0; i < strlen(av[1]); i++){
        if ((abs(av[1][i]) > '9') && av[1][i] != '.')
            return 84;
    }
    for (int i = 0; i < strlen(av[2]); i++){
        if ((abs(av[2][i]) > '9') && av[2][i] != '.')
            return 84;
    }
    for (int i = 1; i < ac; i++) {
        if (chec_verif(av[i]) == 0) {
            printf("Incorrect argument: %s\n", av[i]);
            exit(84);
        }
    }
    return fonction_condition(av, ac);
}
