/*
** EPITECH PROJECT, 2024
** my.c
** File description:
** my_hunter
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/mysprite.h"
#include "my.h"

void display_background(sfRenderWindow *window)
{
    sfTexture *texture = sfTexture_createFromFile("image/Design 1.png", NULL);
    sfSprite *background = sfSprite_create();

    sfRenderWindow_clear(window, sfBlack);
    sfSprite_setTexture(background, texture, sfTrue);
    sfRenderWindow_drawSprite(window, background, NULL);
    sfSprite_destroy(background);
    sfTexture_destroy(texture);
}

sprite_t *initialize_sprites(const char *texture_file, int count)
{
    sfTexture *texture = sfTexture_createFromFile(texture_file, NULL);
    sprite_t *sprites = malloc(count * sizeof(sprite_t));

    for (int i = 0; i < count; i++) {
        sprites[i].sprite = sfSprite_create();
        sfSprite_setTexture(sprites[i].sprite, texture, sfTrue);
        sprites[i].position = (sfVector2f){rand() % 1650, 0};
        sfSprite_setPosition(sprites[i].sprite, sprites[i].position);
        sprites[i].bounds = sfSprite_getGlobalBounds(sprites[i].sprite);
    }
    return sprites;
}

void move_sprites(sprite_t *sprites, int count, sfRenderWindow *window)
{
    int speed = 5;
    static int health = 3;

    for (int i = 0; i < count; i++) {
        sprites[i].position.y += speed;
        if (sprites[i].position.y >= 1024) {
            health--;
            sprites[i].position.y = 0;
            sprites[i].position.x = rand() % 1650;
        }
        if (health <= 0) {
            mini_printf("Game over\n");
            sfRenderWindow_close(window);
        }
        speed += 2;
        sfSprite_setPosition(sprites[i].sprite, sprites[i].position);
        sprites[i].bounds = sfSprite_getGlobalBounds(sprites[i].sprite);
    }
}

static void draw_sprites(sfRenderWindow *window, sprite_t *sprites
    , sfIntRect rect, int count)
{
    for (int i = 0; i < count; i++) {
        sfSprite_setPosition(sprites[i].sprite, sprites[i].position);
        sfSprite_setTextureRect(sprites[i].sprite, rect);
        sfRenderWindow_drawSprite(window, sprites[i].sprite, NULL);
    }
}

static void destroy_sprites(sprite_t *sprites, int count)
{
    for (int i = 0; i < count; i++)
        sfSprite_destroy(sprites[i].sprite);
    free(sprites);
}

static int printf_help(int ac, char **av)
{
    if (ac > 1 && my_strcmp(av[1], "-h") == 0) {
        mini_printf("Welcome to my_hunter a video ");
        mini_printf("game where you must shoot meteorites before ");
        mini_printf("they crash into other planets");
        mini_printf("in order to save humanity from extinction.\n");
        mini_printf("Be careful if 3 meteorites reach the ground, ");
        mini_printf("we lose all connection with the Earth terminal ");
        mini_printf("Good game\n");
        return 1;
    }
    return 0;
}

static void destroy_game(struct_t *hunter)
{
    sfRenderWindow_destroy(hunter->window);
    sfClock_destroy(hunter->clock);
    sfSound_destroy(hunter->sound);
    sfSoundBuffer_destroy(hunter->sound_buffer);
}

void game_loop(struct_t *hunter, int count)
{
    sfIntRect rect = {0, 0, 150, 120};
    sfImage *image = sfImage_createFromFile("image/rocket.png");
    int score = 0;

    hunter->cursor = sfCursor_createFromPixels(sfImage_getPixelsPtr(image)
        , sfImage_getSize(image), (sfVector2u){0, 0});
    while (sfRenderWindow_isOpen(hunter->window)) {
        sfRenderWindow_setFramerateLimit(hunter->window, 60);
        event(hunter->window, hunter->sprites, count);
        handle_animation(hunter->clock, &rect);
        display_background(hunter->window);
        draw_sprites(hunter->window, hunter->sprites, rect, count);
        move_sprites(hunter->sprites, count, hunter->window);
        sfRenderWindow_setMouseCursor(hunter->window, hunter->cursor);
        sfRenderWindow_display(hunter->window);
    }
}

int main(int ac, char **av)
{
    struct_t hunter;
    int menu_result = 0;

    hunter.clock = sfClock_create();
    hunter.sprites = initialize_sprites("image/m.png", 6);
    hunter.sound_buffer = sfSoundBuffer_createFromFile("sound/albator.mp3");
    hunter.sound = sfSound_create();
    if (printf_help(ac, av) == 1)
        return 0;
    hunter.window = sfRenderWindow_create((sfVideoMode){1792, 1024, 32}
        , "MYHUNTER", sfDefaultStyle, NULL);
    menu_result = display_menu(hunter.window);
    if (menu_result == 1) {
        sfSound_setBuffer(hunter.sound, hunter.sound_buffer);
        sfSound_play(hunter.sound);
        game_loop(&hunter, 6);
    }IRE
    return 0;
}
