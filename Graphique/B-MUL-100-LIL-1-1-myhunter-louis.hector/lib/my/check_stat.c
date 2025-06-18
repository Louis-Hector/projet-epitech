/*
** EPITECH PROJECT, 2024
** check_stat.c
** File description:
** defind the stat
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/mysprite.h"
#include "my.h"

static void create_start_button(sfRectangleShape **start_button
    , sfTexture **button_texture)
{
    *start_button = sfRectangleShape_create();
    sfRectangleShape_setSize(*start_button, (sfVector2f){300, 300});
    sfRectangleShape_setPosition(*start_button, (sfVector2f){800, 300});
    *button_texture = sfTexture_createFromFile("image/project.png", NULL);
    sfRectangleShape_setTexture(*start_button, *button_texture, sfTrue);
}

static void make_cond(sfFloatRect *bounds
    , sfVector2f mouse_pos, int *start_game)
{
    if (sfFloatRect_contains(bounds, mouse_pos.x, mouse_pos.y))
        *start_game = 1;
}

static int handle_menu_events(sfRenderWindow *window
    , sfRectangleShape *start_button)
{
    sfEvent event;
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(window
        , sfMouse_getPositionRenderWindow(window), NULL);
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(start_button);
    int start_game = 0;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return -1;
        }
        if (event.type == sfEvtMouseButtonPressed)
            make_cond(&bounds, mouse_pos, &start_game);
    }
    return start_game;
}

int display_menu(sfRenderWindow *window)
{
    sfTexture *menu = sfTexture_createFromFile("image/Design 1.png", NULL);
    sfSprite *menu_sprite = sfSprite_create();
    sfRectangleShape *start_button;
    sfTexture *button_texture;
    int start_game = 0;

    sfSprite_setTexture(menu_sprite, menu, sfTrue);
    create_start_button(&start_button, &button_texture);
    while (sfRenderWindow_isOpen(window) && start_game == 0) {
        start_game = handle_menu_events(window, start_button);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, menu_sprite, NULL);
        sfRenderWindow_drawRectangleShape(window, start_button, NULL);
        sfRenderWindow_display(window);
    }
    sfRectangleShape_destroy(start_button);
    sfTexture_destroy(button_texture);
    sfSprite_destroy(menu_sprite);
    sfTexture_destroy(menu);
    return start_game;
}

static void check_the_mouse(sfRenderWindow *window,
    sprite_t *sprites, int count, int i)
{
    static sfMusic *music = NULL;
    static int score = 0;

    music = sfMusic_createFromFile("sound/mi.mp3");
    sfMusic_setVolume(music, 9.0f);
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        score++;
        sfMusic_stop(music);
        sfMusic_play(music);
        sprites[i].position = (sfVector2f){rand() % 1650, 0};
        sfSprite_setPosition(sprites[i].sprite, sprites[i].position);
        sprites[i].bounds = sfSprite_getGlobalBounds(sprites[i].sprite);
    }
}

void check_collision_with_cursor(sfRenderWindow *window,
    sprite_t *sprites, int count)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);

    if (sfRenderWindow_getSize(window).x != 1792
        || sfRenderWindow_getSize(window).y != 1024) {
        mouse_pos.x = (float)mouse_pos.x * 1792
            / sfRenderWindow_getSize(window).x;
        mouse_pos.y = (float)mouse_pos.y * 1024
            / sfRenderWindow_getSize(window).y;
    }
    for (int i = 0; i < count; i++) {
        if (sfFloatRect_contains(&sprites[i].bounds
            , mouse_pos.x, mouse_pos.y)) {
            check_the_mouse(window, sprites, count, i);
        }
    }
}

void event(sfRenderWindow *window, sprite_t *sprites, int count)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            check_collision_with_cursor(window, sprites, count);
    }
}

void move_rect(sfIntRect *rect, int offset, int max_value)
{
    rect->left += offset;
    if (rect->left >= max_value) {
        rect->left = 0;
    }
}

void handle_animation(sfClock *clock, sfIntRect *rect)
{
    sfTime elapsed_time = sfClock_getElapsedTime(clock);

    if (sfTime_asSeconds(elapsed_time) >= 0.05f) {
        move_rect(rect, 151, 151 * 8);
        sfClock_restart(clock);
    }
}
