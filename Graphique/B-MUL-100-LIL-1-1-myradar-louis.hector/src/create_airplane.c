/*
** EPITECH PROJECT, 2024
** create_airplane.c
** File description:
** create airplane with all informations
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/mysprite.h"
#include <math.h>

void check_distance(airplane_t *airplane, int i, int j, double distance)
{
    if (distance <= (20 + 20)) {
        sfRectangleShape_setFillColor(airplane[i].rectangle, sfWhite);
        sfRectangleShape_setFillColor(airplane[j].rectangle, sfWhite);
        airplane[i].start.x = 2000;
        airplane[j].start.x = 2000;
    }
}

static int is_airplane_near_tower(airplane_t *airplane, int i
    , tower_t *tower, int count_tower)
{
    double distance;
    double dx;
    double dy;

    for (int t = 0; t < count_tower; t++) {
        dx = airplane[i].start.x - tower[t].position.x;
        dy = airplane[i].start.y - tower[t].position.y;
        distance = sqrt(pow(dx, 2) + pow(dy, 2));
        if (distance <= tower[t].radius * 5) {
            return 1;
        }
    }
    return 0;
}

int is_intersecting_rectangle(airplane_t *airplane, int count
    , tower_t *tower, int count_tower)
{
    double Cx;
    double Cy;
    double Dx;
    double Dy;
    double distance;

    for (int i = 0; i < count; i++) {
        if (is_airplane_near_tower(airplane, i, tower, count_tower) == 1)
            continue;
        for (int j = i + 1; j < count; j++) {
            Cx = airplane[i].start.x;
            Cy = airplane[i].start.y;
            Dx = airplane[j].start.x;
            Dy = airplane[j].start.y;
            distance = sqrt(pow(Cx - Dx, 2) + pow(Cy - Dy, 2));
            check_distance(airplane, i, j, distance);
        }
    }
    return 0;
}

static void check_position(airplane_t *airplane, int *count, int *i)
{
    double dx = airplane[*i].start.x - airplane[*i].destination.x;
    double dy = airplane[*i].start.y - airplane[*i].destination.y;
    double distance = sqrt(dx * dx + dy * dy);

    if (distance < 20 || airplane[*i].start.x < 0
        || airplane[*i].start.x >= 1910 ||
        airplane[*i].start.y <= 0 || airplane[*i].start.y >= 1070) {
        sfRectangleShape_destroy(airplane[*i].rectangle);
        for (int j = *i; j < *count - 1; j++)
            airplane[j] = airplane[j + 1];
        (*count)--;
    } else {
        sfSprite_setPosition(airplane[*i].sprite,
            (sfVector2f){(float)airplane[*i].start.x
            , (float)airplane[*i].start.y});
        sfRectangleShape_setPosition(airplane[*i].rectangle,
            (sfVector2f){(float)airplane[*i].start.x
            , (float)airplane[*i].start.y});
    }
}

void move_sprites(airplane_t *airplane, int *count, sfRenderWindow *window)
{
    int new_count = *count;
    sfVector2f direction;
    float direc;

    for (int i = 0; i < new_count; i++) {
        direction.x = airplane[i].destination.x - airplane[i].start.x;
        direction.y = airplane[i].destination.y - airplane[i].start.y;
        direc = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (direc != 0) {
            direction.x /= direc;
            direction.y /= direc;
            airplane[i].start.x += direction.x * airplane[i].speed * 0.2;
            airplane[i].start.y += direction.y * airplane[i].speed * 0.2;
        }
        check_position(airplane, &new_count, &i);
    }
    if (new_count == 0)
        sfRenderWindow_close(window);
    *count = new_count;
}

void draw_sprites(sfRenderWindow *window, airplane_t *airplane, int count)
{
    sfTexture *texture = sfTexture_createFromFile("picture/plane.png", NULL);

    for (int i = 0; i < count; i++) {
        if (airplane[i].start.x > airplane[i].destination.x)
            sfSprite_setRotation(airplane[i].sprite, 180);
        sfSprite_setOrigin(airplane[i].sprite, (sfVector2f){
            sfTexture_getSize(texture).x
            / 2.f, sfTexture_getSize(texture).y / 2.f });
        sfSprite_setScale(airplane[i].sprite, (sfVector2f){20.f
            / sfTexture_getSize(texture).x,
            20.f / sfTexture_getSize(texture).y });
        sfSprite_setPosition(airplane[i].sprite, (sfVector2f){
            airplane[i].start.x, airplane[i].start.y });
        sfRectangleShape_setFillColor(airplane[i].rectangle, sfTransparent);
        sfRenderWindow_drawRectangleShape(window, airplane[i].rectangle, NULL);
        sfRenderWindow_drawSprite(window, airplane[i].sprite, NULL);
    }
    sfTexture_destroy(texture);
}

airplane_t *initialize_airplanes(int count, airplane_t *airplane)
{
    sfTexture *texture = sfTexture_createFromFile("picture/plane.png", NULL);

    if (texture == NULL)
        return NULL;
    for (int i = 0; i < count; i++) {
        airplane[i].sprite = sfSprite_create();
        sfSprite_setTexture(airplane[i].sprite, texture, sfTrue);
        airplane[i].rectangle = sfRectangleShape_create();
        sfRectangleShape_setOutlineColor(airplane[i].rectangle, sfRed);
        sfRectangleShape_setOutlineThickness(airplane[i].rectangle, 3);
        sfRectangleShape_setSize(airplane[i].rectangle, (sfVector2f){20, 20});
        sfRectangleShape_setOrigin(airplane[i].rectangle
            , (sfVector2f){10, 10});
        sfRectangleShape_setPosition(airplane[i].rectangle,
            (sfVector2f){(float)airplane[i].start.x
            , (float)airplane[i].start.y});
    }
    return airplane;
}
