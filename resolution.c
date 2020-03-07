#include "resolution.h"
bool insertionValide(uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint64_t candidat, uint64_t mask)
{

    if((mask|candidat&*bbL &*bbC &*bbB))
    {
        *bbL|=candidat;
       *bbC|=candidat;
        *bbB|=candidat;

        return true;

    }
    else
        return false;

}
void iterativeResolution(size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t** grille, uint8_t** map,Liste** l1)
{
    uint64_t mask = (1<<taille)-1;
    Liste* lp = (*l1);

	//while(nbElementListe(lp)>250)
    while(lp)
    {
        if(lp->population==1)
        {
             if(insertionValide(&bbL[lp->i],&bbC[lp->j],&bbB[map[lp->i][lp->j]],lp->candidats,mask))
            {
                grille[lp->i][lp->j]+=1+lp->c[0];

                (*l1)=rechercheCandidat( taille,  n,bbL, bbC, bbB,grille,map);
                lp = (*l1);

            }

        }
        else
            lp=lp->next;
    }

}
bool resolu(uint8_t** grille, Liste *dl, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map)
{
    if(!dl)
        return true;
    size_t k, i = dl->i, j= dl->j, b = map[i][j];
    for(k = 0 ; k < dl->population ; k++)
    {

        size_t c = dl->c[k];
        uint8_t val = c+1, indice1 = val-1;
        uint64_t bitVal = 1<<indice1;

       if((val && (( (bbL[i] | bbC[j] | bbB[b])>>indice1)&1) == 0))
        {
            grille[i][j] = val;
            bbL[i] |= bitVal;
            bbC[j] |= bitVal;
            bbB[b] |= bitVal;
            if(resolu(grille, dl->next, taille, n, bbL, bbC, bbB,map))
			{
				return true;
			}
        }
    }
    size_t bi =dl->back->i , bj = dl->back->j;
    uint8_t indice2 = grille[bi][bj]-1;
    uint64_t bitVal2 = (1<<indice2);
    bbL[bi] ^= bitVal2;
    bbC[bj] ^= bitVal2;
    bbB[map[bi][bj]] ^= bitVal2;
    return false;
}
