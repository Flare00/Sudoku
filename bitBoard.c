#include "bitBoard.h"

uint32_t* bitboard32Creer(size_t taille)
{
    uint32_t* bb = calloc(taille, sizeof(uint32_t));
	if(!bb) return NULL;
	return bb;
}

uint64_t* bitboard64Creer(size_t taille)
{
    uint64_t* bb = calloc(taille, sizeof(uint64_t));
	if(!bb) return NULL;
	return bb;
}

void bitBoardDetruire(uint64_t *bb)
{
    free(bb);
}

void bitBoardDetruire32(uint32_t *bb)
{
    free(bb);
}

bool bitBoardInitialiser(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
{
    uint64_t un = 1;
    size_t a=0, taille = n*n;
    for(size_t i = 0; i < taille; i++)
    {
        // bbL[i] = 0;
        // bbC[i] = 0;
        size_t minI = (i/n)*n, maxI = minI+n;

        for(size_t j = 0; j < taille; j++)
        {
            if(grille[i][j]){
                /* On ajoute toutes les valeurs de la grille à la ligne i != 0 dans le
                bitBoard ligne (bbL) */
                if((bbL[i]>>(grille[i][j]-un))&un){ //si l'élément existe déjà (pour éviter les répétitions)
                    bitBoardDetruire(bbL);
                    bitBoardDetruire(bbC);
                    bitBoardDetruire(bbB);
                    return false;
                }
                bbL[i] |= un<<(grille[i][j]-1);
              }

            if(grille[j][i]){
                /* On ajoute toutes les valeurs de la grille à la colonne j != 0 dans le
                bitBoard colonne (bbC) */
                if((bbC[i]>>(grille[j][i]-un))&un){
                    bitBoardDetruire(bbL);
                    bitBoardDetruire(bbC);
                    bitBoardDetruire(bbB);
                    return false;
                }
                bbC[i] |= un<<(grille[j][i]-1);
              }


            if(i%n == 0 && j%n == 0){
                // bbB[a] = 0;
                size_t minJ = (j/n)*n, maxJ = minJ+n;
                for (size_t k = minI; k < maxI; k++)
                {
                    for (size_t l = minJ; l < maxJ; l++)
                    {
                        if(grille[k][l]){
                            /* On ajoute toutes les valeurs de la grille du block encadré
                            dans le bitBoard block (bbB) */
                            if((bbB[a]>>(grille[k][l]-un))&un){

                                bitBoardDetruire(bbL);
                                bitBoardDetruire(bbC);
                                bitBoardDetruire(bbB);
                                return false;
                            }
                            bbB[a] |= un<<(grille[k][l]-1);
                          }
                    }
                }
                a++;
            }
        }
    }
    return true;
}

bool bitBoardInitialiser32(uint8_t **grille, size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB)
{
    size_t a=0, taille = n*n;
    for(size_t i = 0; i < taille; i++)
    {
        size_t minI = (i/n)*n, maxI = minI+n;

        for(size_t j = 0; j < taille; j++)
        {
            if(grille[i][j]){
                /* On ajoute toutes les valeurs de la grille à la ligne i != 0 dans le
                bitBoard ligne (bbL) */
                if((bbL[i]>>(grille[i][j]-1))&1){
                    bitBoardDetruire32(bbL);
                    bitBoardDetruire32(bbC);
                    bitBoardDetruire32(bbB);
                    return false;
                }
                bbL[i] |= (uint32_t)1<<(grille[i][j]-1);
              }

            if(grille[j][i]){
                /* On ajoute toutes les valeurs de la grille à la colonne j != 0 dans le
                bitBoard colonne (bbC) */
                if((bbC[i]>>(grille[j][i]-1))&1){
                    bitBoardDetruire32(bbL);
                    bitBoardDetruire32(bbC);
                    bitBoardDetruire32(bbB);
                    return false;
                }
                bbC[i] |= (uint32_t)1<<(grille[j][i]-1);
              }


            if(i%n == 0 && j%n == 0){
                size_t minJ = (j/n)*n, maxJ = minJ+n;
                for (size_t k = minI; k < maxI; k++)
                {
                    for (size_t l = minJ; l < maxJ; l++)
                    {
                        if(grille[k][l]){
                            if((bbB[a]>>(grille[k][l]-1))&1){
                                bitBoardDetruire32(bbL);
                                bitBoardDetruire32(bbC);
                                bitBoardDetruire32(bbB);
                                return false;
                            }
                            bbB[a] |= (uint32_t)1<<(grille[k][l]-1);
                          }
                    }
                }
                a++;
            }
        }
    }
    return true;
}

void bitAfficher(uint64_t candidat, size_t taille)
{
    for(size_t i=0; i< taille; i++)
    {
        // Si le bit de candidat à l'indice i match avec 1, alors on affiche 1
        // Sinon 0
       printf("%ld ", (candidat>>i)&1);
    }
    printf("\n");
}

void bitAfficher32(uint32_t candidat, size_t taille)
{
    for(size_t i=0; i< taille; i++)
    {
        // Si le bit de candidat à l'indice i match avec 1, alors on affiche 1
        // Sinon 0
       printf("%d ", (candidat>>i)&1);
    }
    printf("\n");
}

void bitBoardAfficher(size_t taille, uint64_t* bb)
{
    for(size_t i = 0; i < taille; i++)
    {
        bitAfficher(bb[i], taille);
    }
    return;
}

void bitBoardAfficher32(size_t taille, uint32_t* bb)
{
    for(size_t i = 0; i < taille; i++)
    {
        bitAfficher32(bb[i], taille);
    }
    return;
}

void bitBoardAfficherTout(size_t taille,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
{
    printf("BBL : \n\n");
    bitBoardAfficher(taille, bbL);
    printf("BBC : \n\n");
    bitBoardAfficher(taille, bbC);
    printf("BBB : \n\n");
    bitBoardAfficher(taille, bbB);
    printf("\n");
}

void bitBoardAfficherTout32(size_t taille,uint32_t *bbL, uint32_t *bbC, uint32_t *bbB)
{
    printf("BBL : \n\n");
    bitBoardAfficher32(taille, bbL);
    printf("BBC : \n\n");
    bitBoardAfficher32(taille, bbC);
    printf("BBB : \n\n");
    bitBoardAfficher32(taille, bbB);
    printf("\n");
}
