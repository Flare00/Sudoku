#include "bitBoard.h"

void bitBoardInitialiser(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
{
    size_t a=0, taille = n*n;
    for(size_t i = 0; i < taille; i++)
    {
        bbL[i] = 0;
        bbC[i] = 0;
        size_t minI = (i/n)*n, maxI = minI+n;

        for(size_t j = 0; j < taille; j++)
        {
            if(grille[i][j])
                /* On ajoute toutes les valeurs de la grille à la ligne i != 0 dans le
                bitBoard ligne (bbL) */
                bbL[i] |= 1<<(grille[i][j]-1);

            if(grille[j][i])
                /* On ajoute toutes les valeurs de la grille à la colonne j != 0 dans le
                bitBoard colonne (bbC) */
                bbC[i] |= 1<<(grille[j][i]-1);

            if(i%n == 0 && j%n == 0){
                bbB[a] = 0;
                size_t minJ = (j/n)*n, maxJ = minJ+n;
                for (size_t k = minI; k < maxI; k++)
                {
                    for (size_t l = minJ; l < maxJ; l++)
                    {
                        if(grille[k][l])
                            /* On ajoute toutes les valeurs de la grille du block encadré
                            dans le bitBoard block (bbB) */
                            bbB[a] |= 1<<(grille[k][l]-1);
                    }
                }
                a++;
            }
        }
    }
}

void bitBoardDetruire(uint64_t *bb)
{
    free(bb);
}

void afficherBit(uint64_t candidat, size_t taille)
{
    for(size_t i=0; i< taille; i++)
    {
        // Si le bit de candidat à l'indice i match avec 1, alors on affiche 1
        // Sinon 0
       printf("%ld ", (candidat>>i)&1);
    }
    printf("\n");
}

void afficherBit_64(uint64_t candidat)
{
    for(size_t i=0; i< 64; i++)
    {
        // Si le bit de candidat à l'indice i match avec 1, alors on affiche 1
        // Sinon 0
       printf("%ld", (candidat>>(63-i))&1);
    }
    printf("\n");
}


void afficherTousBitBoard(size_t taille,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
{
    printf("BBL : \n\n");
    afficherBitBoard(taille, bbL);
    printf("BBC : \n\n");
    afficherBitBoard(taille, bbC);
    printf("BBB : \n\n");
    afficherBitBoard(taille, bbB);
    printf("\n");

}
void afficherBitBoard(size_t taille, uint64_t* bb)
{
    for(size_t i = 0; i < taille; i++)
    {
        afficherBit(bb[i], taille);
    }
    return;
}

uint32_t* bitboard32Creer(size_t taille)
{
    uint32_t* bb = malloc(taille * sizeof(uint32_t));
	if(!bb) return NULL;
	return bb;
}

uint64_t* bitboard64Creer(size_t taille)
{
    uint64_t* bb = malloc(taille * sizeof(uint64_t));
	if(!bb) return NULL;
	return bb;
}

