/*
** EPITECH PROJECT, 2024
** pong
** File description:
** who calculate vector
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void hit_the_paddle(int ac, char **av)
{
    double Vx = (atof(av[4]) - atof(av[1]));
    double Vy = (atof(av[5]) - atof(av[2]));
    double Vz = (atof(av[6]) - atof(av[3]));
    double norm = sqrt(Vx * Vx + Vy * Vy + Vz * Vz);
    double angle = Vz / norm;

    if ((atof(av[6]) > 0 && Vz < 0) || (atof(av[6]) < 0 && Vz > 0)) {
        angle = asin(angle) * (180 / M_PI);
        angle = sqrt(angle * angle);
        printf("The incidence angle is:\n%.2f degrees\n", angle);
        return;
    } else if ((atof(av[6]) == 0 && Vz == 0) || (atof(av[6]) == 0 && Vz == 0)) {
        printf("The incidence angle is:\n0.00 degrees\n");
    } else
        printf("The ball won't reach the paddle.\n");
}

int pong(int ac, char **av)
{
    double vx = (atof(av[4]) - atof(av[1]));
    double vy = (atof(av[5]) - atof(av[2]));
    double vz = (atof(av[6]) - atof(av[3]));
    int time = atof(av[7]);
    double future_vz;

    if (time < 0) {
        printf("time invalid");
        return 84;
    }
    printf("The velocity vector of the ball is:\n");
    printf("(%.2f, %.2f, %.2f)\n", vx, vy, vz);
    vx = time * vx + atof(av[4]);
    vy = time * vy + atof(av[5]);
    future_vz = time * vz + atof(av[6]);
    printf("At time t + %d, ball coordinates will be:\n", time);
    printf("(%.2f, %.2f, %.2f)\n", vx, vy, future_vz);
    hit_the_paddle(ac, av);
    return 0;
}

int chec_verif(char const *str)
{
    int i = 0;
    int count = 0;

    if (str[0] == '-') {
        i++;
    }
    while (str[i] != '\0') {
        if (str[i] == '.') {
            count++;
        }
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
            return 0;
        }
        i++;
    }
    return count <= 1;
}

int main(int ac, char **av)
{
    if (ac != 8) {
        printf("Invalid arguments\n");
        return 84;
    }
    for (int i = 1; i <= 6; i++) {
        if (chec_verif(av[i]) == 0) {
            printf("Incorrect argument\n");
            return 84;
        }
    }
    if (my_str_isnum(av[7]) == 0) {
        printf("Time invalid\n");
        return 84;
    }
    pong(ac, av);
}
