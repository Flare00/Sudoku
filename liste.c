#include "bitBoard.h"

uint64_t depilerListe(Liste *dl)
{
    uint64_t candidats;
    Liste *tmp;
    if(!dl) return -1;

    tmp = dl->next;
    candidats = dl->candidats;

    free(dl);
    dl = tmp;
    return candidats;
}

Liste *insertionListe(Liste *dl, uint64_t candidats, size_t i, size_t j)// on passe la liste par référence
{
    Liste *elem = malloc(sizeof(Liste));

    if(!elem) exit(EXIT_FAILURE);
    elem->candidats = candidats;
    elem->population = __builtin_popcountll(candidats);// __builtin_popcount directive de gcc qui compte le nombre de bit d'un mot
    elem->c = malloc(elem->population*sizeof(size_t));

    uint64_t candidat=elem->candidats;
    size_t indice=0;
    for(int p=0; p< elem->population; p++)
    {
        while(candidat)
        {
            if(candidat&1<<indice)
            {
               elem->c[p]= indice;
               candidat^=1<<indice;
                break;
            }

              indice++;
        }
    }
    elem->i=i;
    elem->j=j;
    elem->next = NULL;
    elem->back = NULL;

    if(!dl)
    {
        return elem;
    }

    Liste *cdl = dl;
    while(cdl->population < elem->population && cdl->next)
    {
        cdl = cdl->next;
    }

    if(cdl->population < elem->population)
    {
        Liste *cdlNext = cdl->next;
        cdl->next = elem;
        elem->back = cdl;
        if(cdlNext)
        {
            elem->back = cdlNext;
            cdlNext->next = elem;
        }
    }
    else
    {
        Liste *cslBack = cdl->back;
        cdl->back = elem;
        elem->next = cdl;
        if(cslBack)
        {
            elem->back = cslBack;
            cslBack->next = elem;
        }
        else return elem;
    }
    return dl;
}

void detruireListe(Liste *dl)
{
    while(dl)
    {
        Liste *aSup = dl;
        dl = dl->next;
        free(aSup);
    }
}
size_t nbElementListe(Liste *l1){
    size_t count=0;
    while(l1!=NULL)
    {
        count++;
        l1=l1->next;

    }
    return count;
}
size_t nbCandidatListe(Liste *l1){
    size_t count=0;
    while(l1!=NULL)
    {
        count+=l1->population;
        l1=l1->next;

    }
    return count;
}
void afficherListe(Liste* liste)
{
    while(liste!=NULL)
    {
        printf("%ld : %ld : pop : %d candidats : ", liste->j, liste->i, liste->population);

        afficherBit_64(liste->candidats);
        printf("(");
        for(int i=0; i<liste->population;i++)
        {
            printf("%ld,", liste->c[i]);
        }
        printf(")\n");
        liste=liste->next;
    }
}
