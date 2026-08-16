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
    sfRectangleShape *rectangle;
    sfSprite *sprite;
    sfVector2i start;
    sfVector2i destination;
    int speed;
    int delay;
} airplane_t;

typedef struct tower_values {
    sfCircleShape *circle;
    sfVector2i position;
    int radius;
} tower_t;

typedef struct number_elements {
    int number_plane;
    int nb_tower;
} number_elements_t;

int is_intersecting_rectangle(airplane_t *airplane
    , int count, tower_t *tower, int count_tower);
void move_sprites(airplane_t *airplane, int *count, sfRenderWindow *window);
void draw_sprites(sfRenderWindow *window, airplane_t *airplane
    , int count);
airplane_t *initialize_airplanes(int count, airplane_t *airplane);
int read_script(char **av, airplane_t **airplane, tower_t **tower
    , number_elements_t *number);
int check_error_handling(int ac, char **av);
void print_time(sfClock *clock, sfRenderWindow *window);

#endif
