#include "bitBoard.h"

Liste *insertionListe(Liste *dl, uint64_t candidats, size_t i, size_t j)// on passe la liste par référence
{
    Liste *elem = malloc(sizeof(Liste));

    if(!elem) exit(EXIT_FAILURE);
    elem->candidats = candidats;
    elem->population = __builtin_popcountll(candidats);// __builtin_popcount directive de gcc qui compte le nombre de bit d'un mot
    elem->c = malloc(elem->population*sizeof(size_t));

    uint64_t candidat=elem->candidats;
    size_t indice=0;
    for(int p=0; p < elem->population; p++)
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
    elem->suivante = NULL;
    elem->precedente = NULL;

    if(!dl)
    {
        return elem;
    }

    Liste *cdl = dl;
    while(cdl->population < elem->population && cdl->suivante)
    {
        cdl = cdl->suivante;
    }

    if(cdl->population < elem->population)
    {
        Liste *cdlNext = cdl->suivante;
        cdl->suivante = elem;
        elem->precedente = cdl;
        if(cdlNext)
        {
            elem->precedente = cdlNext;
            cdlNext->suivante = elem;
        }
    }
    else
    {
        Liste *cslBack = cdl->precedente;
        cdl->precedente = elem;
        elem->suivante = cdl;
        if(cslBack)
        {
            elem->precedente = cslBack;
            cslBack->suivante = elem;
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
        dl = dl->suivante;
        free(aSup);
    }
}

size_t nbElementListe(Liste *l1){
    size_t count=0;
    while(l1!=NULL)
    {
        count++;
        l1=l1->suivante;

    }
    return count;
}

size_t nbCandidatListe(Liste *l1){
    size_t count=1;
    while(l1!=NULL)
    {
        count+=l1->population;
        l1=l1->suivante;

    }
    return count;
}

void afficherListe(Liste* liste)
{
    size_t i=0;
    while(liste!=NULL)
    {
        if(i>5)
        {
            printf("\n");
            i=0;
        }
        else{
            printf("%ld : %ld : pop : %d \t", liste->j, liste->i, liste->population);
            i++;
        }
        liste=liste->suivante;
    }
}
