#include "liste.h"

uint64_t Pop(Liste **sl)
{
    uint64_t candidats;
    Liste *tmp;
    if(!*sl) return -1;

    tmp = (*sl)->next;
    candidats = (*sl)->candidats;

    free(*sl);
    *sl = tmp;
    return candidats;
}

void Insert(Liste **sl, uint64_t candidats, size_t i, size_t j)// on passe la liste par référence
{
    Liste *tmp = NULL;
    Liste *csl = *sl;
    Liste *elem = malloc(sizeof(Liste));
    if(!elem) exit(EXIT_FAILURE);

    elem->candidats = candidats;
    elem->population = __builtin_popcount(candidats);// __builtin_popcount directive de gcc qui compte le nombre de bit à 1 d'un mot
    elem->i=i;
    elem->j=j;

    while(csl && csl->population < elem->population)
    {
        tmp = csl;
        csl = csl->next;
    }
    elem->next = csl;
    if(tmp) tmp->next = elem;
    else *sl = elem;
}

void afficherListe(Liste* liste)
{
    while(liste!=NULL)
    {
        printf("%ld : %ld : pop : %d candidats : %ld Binary: \n", liste->j, liste->i, liste->population,liste->candidats);
        afficherBit(liste->candidats, 64);
        liste=liste->next;
    }
}
