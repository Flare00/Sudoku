#include "resolution.h"

int valeurBit(uint64_t bit, size_t indice)
{
	if((bit>>indice)&1) // Si le bit à l'indice i match avec 1
		return indice+1; // On renvoie la valeur entière qu'il représente
	return 0;
}
uint8_t firstBitPosition(size_t min , size_t taille, uint64_t bitWord)
{
    for(size_t i=min; i< taille; i++)
    {
        // Si le bit de candidat à l'indice i match avec 1, alors on affiche 1
        // Sinon 0
       if(bitWord&1<<i)
       {
           return i;
       }
    }
}

int insertionValide(uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint64_t candidat, uint64_t mask)
{

    if((mask|candidat&*bbL &*bbC &*bbB))
    {
        *bbL|=candidat;
       *bbC|=candidat;
        *bbB|=candidat;

        return 1;

    }
    else
        return -1;

}
void res(size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, Liste** l1)
{
    uint64_t mask = (1<<taille)-1;
    Liste* lp = (*l1);

    //while(lp)
	while(nbElementListe(lp)>180)
    {

       if(lp->population==1)
       {

            if(insertionValide(&bbL[lp->i],&bbC[lp->j],&bbB[((lp->i)/n)*n+(lp->j)/n],lp->candidats,mask))
            {
                grille[lp->i][lp->j]+=1+firstBitPosition(0 , taille, lp->candidats);

                (*l1)=rechercheCandidat( taille,  n,bbL, bbC, bbB,grille);
                lp = (*l1);

            }
       }
       else
        lp=lp->next;
    }

}
bool resolu(uint8_t** grille, Liste *dl, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
{
    if(!dl)
        return true;
    size_t k;
    for(k = 0 ; k < dl->population ; k++)
    {

        size_t c = dl->c[k];
        uint8_t val = valeurBit(dl->candidats, c), indice1 = val-1;
        size_t i = dl->i, j= dl->j;
        size_t b = ((i/n)*n)+j/n;
        uint64_t bitVal = 1<<indice1;

       if((val && (( (bbL[i] |bbC[j] |bbB[b])>>indice1)&1) == 0))
        {
            grille[i][j] = val;
            bbL[i] |= bitVal;
            bbC[j] |= bitVal;
            bbB[b] |= bitVal;
            if(resolu(grille, dl->next, taille, n, bbL, bbC, bbB))
			{
				return true;
			}
        }
    }
    uint8_t indice2 = grille[dl->back->i][dl->back->j]-1;
    uint64_t bitVal2 = (1<<indice2);
    bbL[dl->back->i] ^= bitVal2;
    bbC[dl->back->j] ^= bitVal2;
    bbB[((dl->back->i/n)*n)+dl->back->j/n] ^= bitVal2;
    return false;
}
