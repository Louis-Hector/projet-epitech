/*
** EPITECH PROJECT, 2024
** mystruct.h
** File description:
** structure for the square
*/

#ifndef MY_SH_
    #define MY_SH_

    #include <unistd.h>
    #include <stdio.h>
    #include "my.h"

typedef struct process {
    int R;
    int S;
    int Z;
    int T;
    int D;
    int I;
} ProcessStats_t;

typedef struct cpu {
    int user;
    int nice;
    int system;
    int idle;
    int iowait;
    int irq;
    int softirq;
    int steal;
} ProcessCpu_t;


#endif
