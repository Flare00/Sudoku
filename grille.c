#include "grille.h"


void detruireGrille(uint8_t **grille, size_t taille)
{
	for (size_t i = 0; i < taille; i++)
	{
		free(grille[i]);
	}
	free(grille);
}

uint8_t **creerGrille(unsigned int *chaine, size_t taille)
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
                    uint8_t c = chaine[x+j];
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
