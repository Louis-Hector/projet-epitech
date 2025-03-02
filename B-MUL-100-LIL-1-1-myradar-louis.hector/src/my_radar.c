/*
** EPITECH PROJECT, 2024
** my_radar.c
** File description:
** my_radar
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/mysprite.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../include/my.h"

static void destroy_game(sfRenderWindow *window, airplane_t *airplane
    , number_elements_t number, tower_t *tower)
{
    sfRenderWindow_destroy(window);
    for (int i = 0; i < number.number_plane; i++) {
        sfSprite_destroy(airplane[i].sprite);
        sfRectangleShape_destroy(airplane[i].rectangle);
    }
    for (int i = 0; i < number.nb_tower; i++)
        sfCircleShape_destroy(tower[i].circle);
    free(tower);
    free(airplane);
}

static void event(sfRenderWindow *window)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed || event.key.code == sfKeyQ
            || event.key.code == sfKeyEscape)
            sfRenderWindow_close(window);
    }
}

static tower_t *initialize_tower(int count, tower_t *tower)
{
    srand(time(NULL) + rand());
    if (tower == NULL)
        return NULL;
    for (int i = 0; i < count; i++) {
        sfCircleShape_setOrigin(tower[i].circle,
            (sfVector2f){tower[i].radius, tower[i].radius});
        sfCircleShape_setFillColor(tower[i].circle, sfTransparent);
        sfCircleShape_setOutlineColor(tower[i].circle, sfWhite);
        sfCircleShape_setOutlineThickness(tower[i].circle, 3);
        sfCircleShape_setRadius(tower[i].circle, tower[i].radius * 5);
        sfCircleShape_setPosition(tower[i].circle,
            (sfVector2f){(float)tower[i].position.x - tower[i].radius * 5
            , (float)tower[i].position.y - tower[i].radius * 5});
    }
    return tower;
}

static void draw_tower(sfRenderWindow *window, tower_t *tower, int count)
{
    sfTexture *texture = sfTexture_createFromFile("picture/tower.png", NULL);
    sfVector2u texture_size;
    sfSprite *sprite;

    for (int i = 0; i < count; i++) {
        texture_size = sfTexture_getSize(texture);
        sprite = sfSprite_create();
        sfSprite_setTexture(sprite, texture, sfTrue);
        sfSprite_setOrigin(sprite, (sfVector2f){texture_size.x / 2
            , texture_size.y / 2});
        sfSprite_setScale(sprite, (sfVector2f){0.2f, 0.2f});
        sfSprite_setPosition(sprite, (sfVector2f){
            tower[i].position.x - tower[i].radius,
            tower[i].position.y - tower[i].radius});
        sfRenderWindow_drawCircleShape(window, tower[i].circle, NULL);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfSprite_destroy(sprite);
    }
    sfTexture_destroy(texture);
}

void display_background(sfRenderWindow *window)
{
    sfTexture *texture = sfTexture_createFromFile("picture/c.png", NULL);
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
}

void print_information(void)
{
    mini_printf("%s", "Air traffic simulation panel\n");
    mini_printf("%s", "USAGE\n");
    mini_printf("%s", " ./my_radar [OPTIONS] path_to_script\n");
    mini_printf("%s", "  path_to_script The path to the script file.\n");
    mini_printf("%s", "OPTIONS\n");
    mini_printf("%S", " -h print the usage and quit.\n");
    mini_printf("%s", "USER INTERACTIONS\n");
    mini_printf("%s", " 'L' key enable/disable hitboxes and areas.\n");
    mini_printf("%s", " 'S' key enable/disable sprites.\n");
}

int launch_game(sfRenderWindow *window, airplane_t *airplane
    , tower_t *tower, number_elements_t number)
{
    sfClock *clock = sfClock_create();

    airplane = initialize_airplanes(number.number_plane, airplane);
    tower = initialize_tower(number.nb_tower, tower);
    while (sfRenderWindow_isOpen(window)) {
        event(window);
        sfRenderWindow_clear(window, sfBlack);
        display_background(window);
        draw_sprites(window, airplane, number.number_plane);
        move_sprites(airplane, &number.number_plane, window);
        print_time(clock, window);
        is_intersecting_rectangle(airplane, number.number_plane
            , tower, number.nb_tower);
        draw_tower(window, tower, number.nb_tower);
        sfRenderWindow_display(window);
    }
    destroy_game(window, airplane, number, tower);
    return 0;
}

int check_argument(int ac, char **av, char **envp)
{
    if (ac != 2) {
        mini_printf("%s", "./my_radar: bad arguments: 0 given but 84");
        mini_printf("%s", " required retry with -h");
        return 84;
    }
    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        print_information();
        return 0;
    }
    for (int i = 0; envp[i] != NULL; i++) {
        if (my_strcmp(envp[i], "DISPLAY=:0") == 0)
            return 0;
        if (my_strcmp(envp[i], "DISPLAY=:1") == 0)
            return 0;
    }
    return 84;
}

int main(int ac, char **av, char **env)
{
    sfRenderWindow *window;
    airplane_t *airplane = NULL;
    tower_t *tower = NULL;
    number_elements_t number;

    number.nb_tower = 0;
    number.number_plane = 0;
    if (check_argument(ac, av, env) == 84)
        return 84;
    if (check_error_handling(ac, av) == 84)
        return 84;
    if (read_script(av, &airplane, &tower, &number) == 84)
        return 84;
    window = sfRenderWindow_create((sfVideoMode){1920, 1080, 32}
        , "MYRADAR", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    launch_game(window, airplane, tower, number);
}
