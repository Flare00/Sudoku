#include "resolution.h"

int valeurBit(uint64_t bit, size_t indice)
{
	if((bit>>indice)&1) // Si le bit à l'indice i match avec 1
		return indice+1; // On renvoie la valeur entière qu'il représente
	return 0;
}

bool resolu(uint8_t** grille, Liste *dl, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
{
    if(!dl)
        return true;

    size_t k;
    for(k = 0 ; k < taille ; k++)
    {
        uint8_t val = valeurBit(dl->candidats, k), indice1 = val-1;
        size_t b = ((dl->i/n)*n)+dl->j/n;
        if(val && ((bbL[dl->i]>>indice1)&1) == 0 && ((bbC[dl->j]>>indice1)&1) == 0 && ((bbB[b]>>indice1)&1) == 0)
        {
            grille[dl->i][dl->j] = val;
            bbL[dl->i] |= (1<<indice1);
            bbC[dl->j] |= (1<<indice1);
            bbB[b] |= (1<<indice1);
            if(resolu(grille, dl->next, taille, n, bbL, bbC, bbB))
			{
				return true;
			}
        }
    }
    uint8_t indice2 = grille[dl->back->i][dl->back->j]-1;
    bbL[dl->back->i] ^= (1<<indice2);
    bbC[dl->back->j] ^= (1<<indice2);
    bbB[((dl->back->i/n)*n)+dl->back->j/n] ^= (1<<indice2);
    return false;
}