/*
** EPITECH PROJECT, 2024
** my_put_nbr
** File description:
** affiche un nombre
*/

#include "my.h"

void verification_max(void)
{
    my_putchar('2');
    my_putchar('1');
    my_putchar('4');
    my_putchar('7');
    my_putchar('4');
    my_putchar('8');
    my_putchar('3');
    my_putchar('6');
    my_putchar('4');
    my_putchar('8');
}

int my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar(45);
        nb = nb * (-1);
    }
    if (nb == -2147483648) {
        verification_max();
    }
    if (nb <= 9 && nb >= 0) {
        my_putchar(nb + 48);
    } else {
        my_put_nbr(nb / 10);
        my_putchar(nb % 10 + 48);
    }
    return 0;
}
