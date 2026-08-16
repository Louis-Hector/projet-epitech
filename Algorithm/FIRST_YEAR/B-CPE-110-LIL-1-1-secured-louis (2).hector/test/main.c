
#include "../libshell/hashtable.h"

int main(void)
{
    hashtable_t *ht = new_hashtable(&hash, 10);

    ht_insert(ht, "a", " Hello ");
    ht_insert(ht, "b", " Good Bye ");
    ht_insert(ht, " bobby ", "Maintenant");
    ht_insert(ht, " test ", "Maintenant");
    ht_insert(ht, " test ", "Après");
    ht_insert(ht, " BABA ", " je suis baba ");
    ht_insert(ht, "aqzf", " Hello2 ");
    ht_insert(ht, "bqzdjfkl", " Good 2Bye ");
    ht_insert(ht, " bojiqerkbby ", "2Maintenant");
    ht_insert(ht, " teqhigfuodkst ", "2Maintenant");
    ht_insert(ht, " tyqzehjkhfjdest ", "2Après");
    ht_insert(ht, " BAklmakzgruiyiuqoljBA ", " je 2suis baba ");

    ht_delete(ht, " test ");
    ht_dump(ht);
    printf("path of search value : %s\n", ht_search(ht, " BABA "));
    printf("path of search value : %s\n", ht_search(ht, " test "));
    delete_hashtable(ht);
    return 0;
}