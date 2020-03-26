#include "bitBoard.h"

Liste *listeInsertionOrdonnee(Liste *dl, uint64_t candidats, size_t i, size_t j)// on passe la liste par référence
{
    Liste *elem = malloc(sizeof(Liste));
    if(!elem)
    {
        listeDetruire(dl);
        return NULL;
    }

    if(!elem) exit(EXIT_FAILURE);
    elem->candidats = candidats;
    elem->population = __builtin_popcountll(candidats);// __builtin_popcount directive de gcc qui compte le nombre de bit d'un mot
    elem->c = malloc(elem->population*sizeof(size_t));

    uint64_t candidat=elem->candidats;
    size_t indice=0;

    size_t p = 0;
    while(candidat)
    {
        indice = __builtin_ctz(candidat);
        elem->c[p]= indice;
        candidat^=1<<indice;
        p++;
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

void listeDetruire(Liste *dl)
{
    while(dl)
    {
        free(dl->c);
        Liste *aSup = dl;
        dl = dl->suivante;
        free(aSup);
    }
}

size_t listeNbElement(Liste *l1){
    size_t count=0;
    while(l1!=NULL)
    {
        count++;
        l1=l1->suivante;

    }
    return count;
}

size_t listeNbCandidat(Liste *l1){
    size_t count=0;
    while(l1!=NULL)
    {
        count+=l1->population;
        l1=l1->suivante;

    }
    return count;
}

Liste* rechercherCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map)
{
    size_t taille = n*n;
    Liste *liste = NULL;
    uint64_t mask = (1<<taille)-1, cdt = 0;
    for(size_t i = 0; i < taille; i++)
    {
        for(size_t j = 0; j < taille; j++)
        {
            if(!grille[i][j])
            /* Si la valeur dans une case == 0, on ajoute une liste constituée des
               des coordonnées de cette case ainsi que l'entier représentant les candidats */
            {
                if((cdt=mask&(~(bbL[i] | bbC[j] | bbB[map[i][j]]))))
                    liste = listeInsertionOrdonnee(liste, cdt, i, j);
            }
        }
    }
    return liste;
}

void afficherListe(Liste* liste)
{
    while(liste!=NULL)
    {
        printf("i : %ld j : %ld  b : %ld, pop : %d et (", liste->i, liste->j,block(liste->i,liste->j,5), liste->population);

        for(size_t j=0 ; j<liste->population;j++)
                printf(" %ld, ", liste->c[j]);
            printf(")\n");
        liste=liste->suivante;
    }
}
