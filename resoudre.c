#include "resoudre.h"


void detruireGrille(uint8_t **grille, size_t taille)
{
	for (size_t i = 0; i < taille; i++)
	{
		free(grille[i]);
	}
	free(grille);
}

uint8_t **creerGrille(unsigned int *entree, size_t taille)
{
	uint8_t **grille = malloc(taille * sizeof(uint8_t*));
	if(grille != NULL)
    {
        for (size_t i = 0; i < taille; i++)
        {
            grille[i] = malloc(taille * sizeof(uint8_t));

            if(grille[i] != NULL)
            {
                size_t x = i*taille;
                for (size_t j = 0; j < taille; j++)
                {
                    uint8_t c = entree[x+j];
                    grille[i][j] = c;
                }
            }
            else{
                detruireGrille(grille, i);
                printf("Erreur d'allocation de mémoire !\n");
                exit(1);
            }
        }
    }
    else{
        printf("Erreur d'allocation de mémoire !\n");
        exit(1);
    }
	return grille;
}


void afficherGrille(size_t taille, size_t n, uint8_t **grille)
{
	printf("\n\nGrille : \n");
	for(size_t i = 0; i < taille; i++)
	{
	    if(i%n==0)
        {
            for(size_t k=0;k<12;k++)
                printf(" - ");
            printf("\n");
        }

		for(size_t j = 0; j < taille; j++)
		{
		    if(j%n==0)
                printf(" | ");
            printf(" %d ", grille[i][j]);
		}
		printf("\n");

	}
	printf("\n");
}

void initialiser_bitBoard(uint8_t **grille, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
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

void detruire_bitBoard(uint64_t *bb)
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

void afficherBitBoard(size_t taille, uint64_t* bb)
{
    for(size_t i = 0; i < taille; i++)
    {
        afficherBit(bb[i], taille);
    }
    return;
}