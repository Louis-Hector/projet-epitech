/*
** EPITECH PROJECT, 2024
** my_sort_int_array
** File description:
** description
*/


void dos_boucle(int *array, int size, int iteration)
{
    int j;
    int temp;

    for (j = 0; j < size - iteration - 1; j++) {
        if (array[j] > array[j + 1]) {
            temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
        }
    }
}

void my_sort_int_array(int *array, int size)
{
    int i;

    if (size <= 0) {
        return;
    }
    for (i = 0; i < size - 1; i++) {
        dos_boucle(array, size, i);
    }
}
