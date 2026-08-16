/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** core
*/

#include "my.h"

static void prepare_potions(druid_t *druid)
{
    pthread_mutex_lock(&druid->info->village_action);
    druid->info->beverage_left = druid->info->pot_size;
    druid->info->nb_refills--;
    printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware "
        "I can only make %d more refills after this one.\n",
        druid->info->nb_refills);
    druid->info->already_pano = false;
    pthread_mutex_unlock(&druid->info->village_action);
    for (int i = 0; i < druid->info->nb_villagers; i++)
        sem_post(&druid->info->launch_villager);
}

void *druid_actions(void *args)
{
    druid_t *druid = (druid_t *)args;

    printf("Druid: I'm ready... but sleepy...\n");
    while (druid->info->nb_refills > 0
        && druid->info->villagers_left != druid->info->nb_villagers) {
        sem_wait(&druid->info->launch_druid);
        if (druid->info->villagers_left != druid->info->nb_villagers) {
            prepare_potions(druid);
        }
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    for (int i = 0; i < druid->info->nb_villagers; i++)
        sem_post(&druid->info->launch_villager);
    return NULL;
}

static void go_fight(villager_t *villager)
{
    villager->info->beverage_left--;
    pthread_mutex_unlock(&villager->info->village_action);
    villager->nb_fight--;
    printf("Villager %d: Take that roman scum! Only %d left.\n",
        villager->id, villager->nb_fight);
    return;
}

int need_pano(villager_t *villager)
{
    printf("Villager %d: I need a drink... I see %d servings left.\n",
        villager->id, villager->info->beverage_left);
    if (villager->info->beverage_left == 0) {
        if (villager->info->nb_refills == 0)
            return 1;
        if (villager->info->already_pano == false) {
            villager->info->already_pano = true;
            printf("Villager %d: Hey Pano wake up! We need more potion.\n",
                villager->id);
            sem_post(&villager->info->launch_druid);
        }
        pthread_mutex_unlock(&villager->info->village_action);
        sem_wait(&villager->info->launch_villager);
        pthread_mutex_lock(&villager->info->village_action);
        go_fight(villager);
        return 2;
    }
    return 0;
}

static void time_to_sleep(villager_t *villager)
{
    pthread_mutex_lock(&villager->info->village_action);
    villager->info->villagers_left++;
    if (villager->info->villagers_left == villager->info->nb_villagers)
        sem_post(&villager->info->launch_druid);
    pthread_mutex_unlock(&villager->info->village_action);
    printf("Villager %d: I'm going to sleep now.\n", villager->id);
}

void *villager_actions(void *args)
{
    villager_t *villager = (villager_t *)args;
    int value_return = 0;

    printf("Villager %d: Going into battle!\n", villager->id);
    while (villager->nb_fight > 0) {
        pthread_mutex_lock(&villager->info->village_action);
        value_return = need_pano(villager);
        if (value_return == 1) {
            pthread_mutex_unlock(&villager->info->village_action);
            break;
        }
        if (value_return == 2) {
            continue;
        }
        go_fight(villager);
    }
    time_to_sleep(villager);
    return NULL;
}

int init_village(info_village_t *args, druid_t *druid, villager_t *villagers)
{
    args->beverage_left = args->pot_size;
    args->already_pano = false;
    druid->info = args;
    if (pthread_create(&druid->thread_druid, NULL, druid_actions, druid) != 0)
        return 84;
    for (int i = 0; i < args->nb_villagers; i++) {
        villagers[i].id = i;
        villagers[i].nb_fight = args->nb_fights;
        villagers[i].info = args;
        if (pthread_create(&villagers[i].thread_villager
                , NULL, villager_actions, &villagers[i]) != 0)
            return 84;
    }
    return 0;
}

int launch_panoramix(info_village_t *args)
{
    villager_t villagers[args->nb_villagers];
    druid_t druid;

    if (pthread_mutex_init(&args->village_action, NULL) == -1 ||
        sem_init(&args->launch_druid, 0, 0) == -1
        || sem_init(&args->launch_villager, 0, 0) == -1)
        return 84;
    if (init_village(args, &druid, villagers) == 84)
        return 84;
    if (pthread_join(druid.thread_druid, NULL) != 0)
        return 84;
    for (int i = 0; i < args->nb_villagers; i++)
        if (pthread_join(villagers[i].thread_villager, NULL) != 0)
            return 84;
    if (pthread_mutex_destroy(&args->village_action) == -1 ||
        sem_destroy(&args->launch_druid) == -1
        || sem_destroy(&args->launch_villager) == -1)
        return 84;
    return 0;
}
