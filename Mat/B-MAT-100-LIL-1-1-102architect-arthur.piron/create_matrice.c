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
#include <math.h>

static double **function(double x, double y)
{
    double **matrice = malloc(sizeof(double *) * 3);

    for (int i = 0; i < 3; i++) {
        matrice[i] = malloc(sizeof(double) * 3);
    }
    matrice[0][0] = x;
    matrice[1][0] = y;
    matrice[2][0] = 1;
    return matrice;
}

static double **matrice_translation(double i, double j)
{
    double **matrice = malloc(sizeof(double *) * 3);

    for (int a = 0; a < 3; a++) {
        matrice[a] = malloc(sizeof(double) * 3);
    }
    matrice[0][0] = 1;
    matrice[0][1] = 0;
    matrice[0][2] = i;
    matrice[1][0] = 0;
    matrice[1][1] = 1;
    matrice[1][2] = j;
    matrice[2][0] = 0;
    matrice[2][1] = 0;
    matrice[2][2] = 1;
    return matrice;
}

static double **matrice_scaling(double m, double n)
{
    double **matrice = malloc(sizeof(double *) * 3);

    for (int a = 0; a < 3; a++) {
        matrice[a] = malloc(sizeof(double) * 3);
    }
    matrice[0][0] = m;
    matrice[0][1] = 0;
    matrice[0][2] = 0;
    matrice[1][0] = 0;
    matrice[1][1] = n;
    matrice[1][2] = 0;
    matrice[2][0] = 0;
    matrice[2][1] = 0;
    matrice[2][2] = 1;
    return matrice;
}

static double **matrice_rotation(double d)
{
    double **matrice = malloc(sizeof(double *) * 3);
    double radians = d * M_PI / 180.0;

    for (int a = 0; a < 3; a++) {
        matrice[a] = malloc(sizeof(double) * 3);
    }
    matrice[0][0] = cos(radians);
    matrice[0][1] = -sin(radians);
    matrice[0][2] = 0;
    matrice[1][0] = sin(radians);
    matrice[1][1] = cos(radians);
    matrice[1][2] = 0;
    matrice[2][0] = 0;
    matrice[2][1] = 0;
    matrice[2][2] = 1;
    return matrice;
}

static double **matrice_reflection(double d)
{
    double **matrice = malloc(sizeof(double *) * 3);
    double radians = d * M_PI / 180.0;

    for (int a = 0; a < 3; a++) {
        matrice[a] = malloc(sizeof(double) * 3);
    }
    matrice[0][0] = cos(2 * radians);
    matrice[0][1] = sin(2 * radians);
    matrice[0][2] = 0;
    matrice[1][0] = sin(2 * radians);
    matrice[1][1] = -cos(2 * radians);
    matrice[1][2] = 0;
    matrice[2][0] = 0;
    matrice[2][1] = 0;
    matrice[2][2] = 1;
    return matrice;
}

double **function_translation(double *x, double *y, double i, double j)
{
    double **matrice1 = function(*x, *y);
    double **matrice2 = matrice_translation(i, j);
    double **tab = malloc(sizeof(double *) * 3);
    double x_prime = matrice2[0][0] * matrice1[0][0] + matrice2[0][1]
        * matrice1[1][0] + matrice2[0][2] * matrice1[2][0];
    double y_prime = matrice2[1][0] * matrice1[0][0] + matrice2[1][1]
        * matrice1[1][0] + matrice2[1][2] * matrice1[2][0];
    double z_prime = matrice2[2][0] * matrice1[0][0] + matrice2[2][1]
        * matrice1[1][0] + matrice2[2][2] * matrice1[2][0];

    for (int a = 0; a < 3; a++)
        tab[a] = malloc(sizeof(double) * 1);
    tab[0][0] = x_prime;
    tab[1][0] = y_prime;
    tab[2][0] = z_prime;
    printf("Translation along vector (%d, %d)\n", (int)i, (int)j);
    printf_matrice(matrice2);
    printf("(%.2f, %.2f) => (%.2f, %.2f)\n", matrice1[0][0]
        , matrice1[1][0], tab[0][0], tab[1][0]);
    return tab;
}

double **function_scaling(double *x, double *y, double m, double n)
{
    double **matrice1 = function(*x, *y);
    double **matrice2 = matrice_scaling(m, n);
    double **tab = malloc(sizeof(double *) * 3);
    double x_prime = matrice2[0][0] * matrice1[0][0] + matrice2[0][1]
        * matrice1[1][0] + matrice2[0][2] * matrice1[2][0];
    double y_prime = matrice2[1][0] * matrice1[0][0] + matrice2[1][1]
        * matrice1[1][0] + matrice2[1][2] * matrice1[2][0];
    double z_prime = matrice2[2][0] * matrice1[0][0] + matrice2[2][1]
        * matrice1[1][0] + matrice2[2][2] * matrice1[2][0];

    for (int a = 0; a < 3; a++)
        tab[a] = malloc(sizeof(double) * 1);
    tab[0][0] = x_prime;
    tab[1][0] = y_prime;
    tab[2][0] = z_prime;
    printf("Scaling by factors %d and %d\n", (int)m, (int)n);
    printf_matrice(matrice2);
    printf("(%.2f, %.2f) => (%.2f, %.2f)\n", matrice1[0][0]
        , matrice1[1][0], tab[0][0], tab[1][0]);
    return tab;
}

double **function_rotation(double *x, double *y, double d)
{
    double **matrice1 = function(*x, *y);
    double **matrice2 = matrice_rotation(d);
    double **tab = malloc(sizeof(double *) * 3);
    double x_prime = matrice2[0][0] * matrice1[0][0] + matrice2[0][1]
        * matrice1[1][0] + matrice2[0][2] * matrice1[2][0];
    double y_prime = matrice2[1][0] * matrice1[0][0] + matrice2[1][1]
        * matrice1[1][0] + matrice2[1][2] * matrice1[2][0];
    double z_prime = matrice2[2][0] * matrice1[0][0] + matrice2[2][1]
        * matrice1[1][0] + matrice2[2][2] * matrice1[2][0];

    for (int a = 0; a < 3; a++)
        tab[a] = malloc(sizeof(double) * 1);
    tab[0][0] = x_prime;
    tab[1][0] = y_prime;
    tab[2][0] = z_prime;
    printf("Rotation by a %d degree angle\n", (int)d);
    printf_matrice(matrice2);
    printf("(%.2f, %.2f) => (%.2f, %.2f)\n", matrice1[0][0]
        , matrice1[1][0], tab[0][0], tab[1][0]);
    return tab;
}

double **function_reflexion(double *x, double *y, double d)
{
    double **matrice1 = function(*x, *y);
    double **matrice2 = matrice_reflection(d);
    double **tab = malloc(sizeof(double *) * 3);
    double x_prime = matrice2[0][0] * matrice1[0][0] + matrice2[0][1]
        * matrice1[1][0] + matrice2[0][2] * matrice1[2][0];
    double y_prime = matrice2[1][0] * matrice1[0][0] + matrice2[1][1]
        * matrice1[1][0] + matrice2[1][2] * matrice1[2][0];
    double z_prime = matrice2[2][0] * matrice1[0][0] + matrice2[2][1]
        * matrice1[1][0] + matrice2[2][2] * matrice1[2][0];

    tab = mallocalisation(tab);
    tab[0][0] = x_prime;
    tab[1][0] = y_prime;
    tab[2][0] = z_prime;
    printf("Reflection over an axis with ");
    printf("an inclination angle of %d degrees\n", (int)d);
    printf_matrice(matrice2);
    printf("(%.2f, %.2f) => (%.2f, %.2f)\n", matrice1[0][0]
        , matrice1[1][0], tab[0][0], tab[1][0]);
    return tab;
}
