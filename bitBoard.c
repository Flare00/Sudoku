#include "bitBoard.h"

void initialiserBitBoard(uint8_t **grille, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
{
    size_t a = 0;
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

void detruireBitBoard(uint64_t *bb)
{
    free(bb);
}

void afficherBit(uint64_t candidat)
{
    for(size_t i=0; i< DIMENSION*DIMENSION; i++)
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


void afficherBitBoard(size_t taille, uint64_t* bb)
{
    for(size_t i = 0; i < taille; i++)
    {
        afficherBit(bb[i]);
    }
    return;
}

Liste* rechercheCandidat(size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille)
{
    Liste *liste = NULL;

    for(size_t i = 0; i < taille; i++)
    {
        size_t tmp = (i/n)*n;
        for(size_t j = 0; j < taille; j++)
        {
            if(!grille[i][j])
            /* Si la valeur dans une case == 0, on ajoute une liste constituée des
               des coordonnées de cette case ainsi que l'entier représentant les candidats */
            {
                uint64_t mask = pow(2,taille)-1;
                liste = insertionListe(liste, mask&(~(bbL[i] | bbC[j] | bbB[tmp+j/n])), i, j);
            }
        }
    }

    return liste;
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
    uint64_t mask = pow(2,taille)-1;
    Liste* lp = (*l1);

    while(lp!=NULL)
    {

       if(lp->population==1)
       {

            if(insertionValide(&bbL[lp->i],&bbC[lp->j],&bbB[((lp->i)/n)*n+(lp->j)/n],lp->candidats,mask))
            {
                grille[lp->i][lp->j]+=1+log2(lp->candidats);

                printf("candidat : %d\n", 1+(int)log2(lp->candidats));

                (*l1)=rechercheCandidat( taille,  n,bbL, bbC, bbB,grille);
                lp = (*l1);

            }
       }
       else
        lp=lp->next;
    }

}
