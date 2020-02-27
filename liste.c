#include "bitBoard.h"

uint64_t depilerListe(Liste *sl)
{
    uint64_t candidats;
    Liste *tmp;
    if(!sl) return -1;

    tmp = sl->next;
    candidats = sl->candidats;

    free(sl);
    sl = tmp;
    return candidats;
}

Liste *insertionListe(Liste *sl, uint64_t candidats, size_t i, size_t j)// on passe la liste par référence
{
    Liste *tmp = NULL;
    Liste *csl = sl;
    Liste *elem = malloc(sizeof(Liste));
    if(!elem) exit(EXIT_FAILURE);

    elem->candidats = candidats;
    elem->population = __builtin_popcountll(candidats);// __builtin_popcount directive de gcc qui compte le nombre de bit d'un mot
    elem->i=i;
    elem->j=j;

    while(csl && csl->population < __builtin_popcountll(candidats))
    {
        tmp = csl;
        csl = csl->next;
    }
    elem->next = csl;
    if(tmp) tmp->next = elem;
    else sl = elem;
    return sl;
}

void detruireListe(Liste *sl)
{
    while(sl)
    {
        Liste *aSup = sl;
        sl = sl->next;
        free(aSup);
    }
}

void afficherListe(Liste* liste)
{
    while(liste!=NULL)
    {
        printf("%ld : %ld : pop : %d candidats : ", liste->j, liste->i, liste->population);
        afficherBit_64(liste->candidats);
        liste=liste->next;
    }
}
