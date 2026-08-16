/*
** EPITECH PROJECT, 2023
** B-CPE-110 : Secured
** File description:
** hashtable.h
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef HASHTABLE_H
    #define HASHTABLE_H

typedef struct tab_s {
    int cipher_value;
    char *path;
    int id;
    struct tab_s *next;
} tab_t;

typedef struct hashtable_s {
    int len;
    int (*hash)(char *, int);
    tab_t **tab;
} hashtable_t;

typedef struct linked_list_s {
    tab_t *current;
    tab_t *previous;
} linked_list_t;


// Hash function
int hash(char *key, int len);

// Create & destro table
hashtable_t *new_hashtable(int (*hash)(char *, int), int len);
void delete_hashtable(hashtable_t *ht);

// Handle table
int ht_insert(hashtable_t *ht, char *key, char *value);
int ht_delete(hashtable_t *ht, char *key);
char *ht_search(hashtable_t *ht, char *key);
void ht_dump(hashtable_t *ht);

#endif /* HASHTABLE_H */
