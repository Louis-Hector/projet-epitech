/*
** EPITECH PROJECT, 2024
** mysprite
** File description:
** structure for the sprite
*/

#ifndef MY_SH_
    #define MY_SH_

    #include <unistd.h>
    #include <stdio.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>

typedef struct sprite_values {
    sfSprite *sprite;
    sfVector2f position;
    sfFloatRect bounds;
} sprite_t;

typedef struct {
    sfRenderWindow *window;
    sfClock *clock;
    sprite_t *sprites;
    sfSound *sound;
    sfSoundBuffer *sound_buffer;
    sfCursor *cursor;
} struct_t;

#endif
