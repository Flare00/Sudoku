#include "resolution.h"

Liste* ajouterEnTete(Liste *liste, uint64_t candidats, size_t i, size_t j)
{
    Liste *elem = malloc(sizeof(Liste));
    if(!elem) exit(EXIT_FAILURE);
    elem->candidats = candidats;
    elem->population = 1;
    elem->i=i;
    elem->j=j;
    elem->precedente = NULL;
    elem->suivante = liste;

    return elem;
}

Liste* creerListeUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille)
{
    size_t taille = n*n;
    Liste *liste = NULL;
    uint64_t mask = (1<<taille)-1, cdt;
    for(size_t i = 0; i < taille; i++)
    {
        size_t tmp = (i/n)*n;
        for(size_t j = 0; j < taille; j++)
        {
            if(!grille[i][j] && __builtin_popcountll((cdt=mask&(~(bbL[i] | bbC[j] | bbB[tmp+j/n])))) == 1)
            {
                liste = ajouterEnTete(liste, cdt, i, j);
            }
        }
    }
    return liste;
}

void heuristiqueUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille)
{
    Liste* liste = creerListeUniqueCandidat(n, bbL, bbC, bbB, grille);

    if(liste == NULL) return;

    Liste *courante = liste;
    while(courante!=NULL)
    {
        grille[courante->i][courante->j]=1+__builtin_ctz(courante->candidats);
        size_t indice1 = grille[courante->i][courante->j]-1;
        bbL[courante->i] |= (1<<indice1);
        bbC[courante->j] |= (1<<indice1);
        bbB[((courante->i/n)*n)+courante->j/n] |= (1<<indice1);
        courante = courante->suivante;
    }
    listeDetruire(liste);
    heuristiqueUniqueCandidat(n, bbL, bbC, bbB, grille);
}

void heuristiquePaireCachee(size_t taille,Liste *dl,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t**map)
{
    Liste * sl = dl;
    Liste * al = dl;
    while(sl!=NULL)
    {
        al=dl;
        size_t i,j,b;
        i = sl->i;
        j=sl->j;
        b=map[sl->i][sl->j];
        int pop = sl->population;
        uint64_t candidats = sl->candidats;

        uint64_t mask = (1<<taille)-1;


        while(al!=NULL)
        {
            if(pop==al->population && al->population==2 && (al->i == i||al->j==j||map[al->i][al->j]==b) && candidats==al->candidats)
            {

                if(al->i == i && al->j!=j&&map[al->i][al->j]!=b)
                {

                   bbC[al->i]|=mask&candidats;
                   bbB[map[al->i][al->j]]|=mask&candidats;
                }

                if(al->i != i && al->j==j && map[al->i][al->j]!=b)
                {

                   bbL[i]|=mask&candidats;
                   bbB[b]|=mask&candidats;
                }
                if(al->i != i && al->j!=j&&map[al->i][al->j]==b)
                {

                   bbL[i]|=mask&candidats;
                   bbC[j]|=mask&candidats;

                }
            }
                al=al->suivante;
        }
        sl=sl->suivante;
    }
}

bool resoudreRecursivement(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map)
{
    if(!dl)
        return true;
    size_t k, i = dl->i, j= dl->j, b = map[i][j];
    for(k = 0 ; k < dl->population ; k++)
    {

        size_t c = dl->c[k];
        uint8_t val = c+1, indice1 = val-1;
        uint64_t bitVal = 1<<indice1;

       if((val && !(( (bbL[i] | bbC[j] | bbB[b])>>indice1)&1)))
        {
            grille[i][j] = val;
            bbL[i] |= bitVal;
            bbC[j] |= bitVal;
            bbB[b] |= bitVal;
            if(resoudreRecursivement(grille, dl->suivante, bbL, bbC, bbB,map))
			{
				return true;
			}
        }
    }
    if(dl->precedente)
    {
        size_t bi =dl->precedente->i , bj = dl->precedente->j;
        uint64_t bitVal2 = (1<<(grille[bi][bj]-1));
        bbL[bi] ^= bitVal2;
        bbC[bj] ^= bitVal2;
        bbB[map[bi][bj]] ^= bitVal2;
    }
    grille[i][j] = 0;
    return false;
}
