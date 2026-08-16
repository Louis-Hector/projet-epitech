/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** Task04
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Check if the character is a delimiter.
 *
 * This function checks if the given character is present in the
 * delimiters string.
 *
 * @param c The character to check.
 * @param delimiters The string of delimiters.
 * @return 1 if the character is a delimiter, 0 otherwise.
 */
static int is_delimiter(char c, char const *delimiters)
{
    for (int i = 0; delimiters[i] != '\0'; i++) {
        if (c == delimiters[i])
            return 1;
    }
    return 0;
}

/**
 * @brief Update the word state based on the current character.
 *
 * This function updates the word count and the in_word state
 * based on whether the current character is a delimiter or not.
 *
 * @param c The current character.
 * @param delimiters The string of delimiters.
 * @param count Pointer to the word count.
 * @param in_word Pointer to the in_word state.
 */
static void update_word_state(char c,
    char const *delimiters, int *count, int *in_word)
{
    int is_delim = is_delimiter(c, delimiters);

    if (!is_delim && !(*in_word)) {
        (*count)++;
    }
    *in_word = !is_delim;
}

/**
 * @brief Count the number of words in the string.
 *
 * This function counts the number of words in the given string
 * based on the specified delimiters.
 *
 * @param str The input string.
 * @param delimiters The string of delimiters.
 * @return The number of words in the string.
 */
static int count_words(char const *str, char const *delimiters)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        update_word_state(str[i], delimiters, &count, &in_word);
    }
    return count;
}

/**
 * @brief Get the length of a word in the string.
 *
 * This function calculates the length of a word starting from
 * the given index until a delimiter is encountered.
 *
 * @param str The input string.
 * @param index The starting index of the word.
 * @param delimiters The string of delimiters.
 * @return The length of the word.
 */
static int word_length(char const *str, int index, char const *delimiters)
{
    int length = 0;

    while (str[index] != '\0' && !is_delimiter(str[index], delimiters)) {
        length++;
        index++;
    }
    return length;
}

/**
 * @brief Allocate memory for a word and copy it from the string.
 *
 * This function allocates memory for a word of the specified length
 * and copies the characters from the input string into the allocated
 * memory.
 *
 * @param str The input string.
 * @param start The starting index of the word.
 * @param length The length of the word.
 * @return A pointer to the allocated word, or NULL on failure.
 */
static char *allocate_word(char const *str, int start, int length)
{
    char *word = malloc(sizeof(char) * (length + 1));

    if (!word)
        return NULL;
    for (int i = 0; i < length; i++)
        word[i] = str[start + i];
    word[length] = '\0';
    return word;
}

/**
 * @brief Free the allocated memory for the array of words.
 *
 * This function frees the memory allocated for each word in the
 * array and then frees the array itself.
 *
 * @param array The array of words to free.
 * @param size The size of the array.
 * @return NULL after freeing the memory.
 */
static char **free_array(char **array, int size)
{
    for (int i = 0; i < size; i++)
        free(array[i]);
    free(array);
    return NULL;
}

/**
 * @brief Fill the array with words from the string.
 *
 * This function fills the array with words extracted from the
 * input string based on the specified delimiters.
 *
 * @param str The input string.
 * @param delimiters The string of delimiters.
 * @param array The array to fill with words.
 * @param word_count The number of words to fill.
 * @return A pointer to the filled array, or NULL on failure.
 */
static char **fill_word_array(char const *str,
    char const *delimiters, char **array, int word_count)
{
    int i = 0;
    int word_index = 0;
    int len = 0;

    while (str[i] != '\0' && word_index < word_count) {
        while (is_delimiter(str[i], delimiters))
            i++;
        if (str[i] == '\0')
            break;
        len = word_length(str, i, delimiters);
        array[word_index] = allocate_word(str, i, len);
        if (!array[word_index])
            return free_array(array, word_index);
        word_index++;
        i += len;
    }
    array[word_index] = NULL;
    return array;
}

/**
 * @brief Convert a string into an array of words based on delimiters.
 *
 * This function takes a string and a set of delimiters, counts the
 * number of words in the string, allocates memory for an array of
 * strings, and fills the array with the words extracted from the
 * input string.
 *
 * @param str The input string to split.
 * @param delimiters The string of delimiters.
 * @return A pointer to the array of words, or NULL on failure.
 */
char **my_str_to_word_array(char const *str, char const *delimiters)
{
    int word_count = 0;
    char **array = NULL;

    if (str == NULL)
        return NULL;
    word_count = count_words(str, delimiters);
    array = malloc(sizeof(char *) * (word_count + 1));
    if (!array)
        return NULL;
    return fill_word_array(str, delimiters, array, word_count);
}
