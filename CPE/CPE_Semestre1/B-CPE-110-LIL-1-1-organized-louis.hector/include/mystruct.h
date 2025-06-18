/*
** EPITECH PROJECT, 2023
** B-CPE-110 : Shell Boostrap
** File description:
** bootstrap.h
*/

#ifndef BOOTSTRAP_H
    #define BOOTSTRAP_H

typedef enum type {
    ACTUATOR,
    DEVICE,
    PROCESSOR,
    SENSOR,
    WIRE,
} type_t;

typedef struct node_s {
    int num;
    type_t type;
    char *name;
    struct node_s *next;
} linked_node_t;

#endif
