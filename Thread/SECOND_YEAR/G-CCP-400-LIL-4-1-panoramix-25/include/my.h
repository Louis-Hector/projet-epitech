/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** my.h
*/

#ifndef INCLUDE_H_
    #define INCLUDE_H_
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <stdbool.h>

typedef struct info_village_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    bool already_pano;
    int beverage_left;
    int villagers_left;
    pthread_mutex_t village_action;
    sem_t launch_druid;
    sem_t launch_villager;
} info_village_t;

typedef struct villager_s {
    pthread_t thread_villager;
    int id;
    int nb_fight;
    info_village_t *info;
} villager_t;

typedef struct druid_s {
    pthread_t thread_druid;
    info_village_t *info;
} druid_t;

int launch_panoramix(info_village_t *args);

#endif /* !INCLUDE_H_ */
