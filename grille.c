#include "grille.h"

uint8_t **grilleCreer(uint8_t *chaine, size_t taille)
{
	uint8_t **grille = calloc(taille, sizeof(uint8_t*));
	if(grille != NULL)
    {
        for (size_t i = 0; i < taille; i++)
        {
            grille[i] = calloc(taille, sizeof(uint8_t));

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
                detruire2D(grille, i);
                //printf("Erreur d'allocation de mémoire !\n");
                return NULL;
            }
        }
    }
    else{
        //printf("Erreur d'allocation de mémoire !\n");
        return NULL;
    }
	return grille;
}

uint8_t** mapCreer(size_t n)
{
    size_t taille = n*n;
    uint8_t **map = calloc(taille, sizeof(uint8_t*));
    if(!map) return NULL;
    for (size_t i = 0; i < taille; i++)
    {
        map[i] = calloc(taille, sizeof(uint8_t));
        if(!map[i])
        {
            detruire2D(map, i); //puisque map est de la même dimension que grille, on peut utiliser detruire2D
            return NULL;
        }
    }
    for (size_t i = 0; i < taille; i++)
    {
        for (size_t j = 0; j < taille; j++)
        {
            map[i][j] = block(i,j,n);
        }
    }

    return map;
}

void detruire2D(uint8_t **tableau2D, size_t taille)
{
	for (size_t i = 0; i < taille; i++)
	{
		free(tableau2D[i]);
	}
	free(tableau2D);
}

void afficher2D(size_t n, uint8_t **grille)
{
	size_t taille = n*n;
	printf("\n\nGrille : \n");
	for(size_t i = 0; i < taille; i++)
	{
	    if(i%n==0)
        {
            for(size_t k=0;k<(n+1)*n;k++)
                printf(" - ");
            printf("\n");
        }

		for(size_t j = 0; j < taille; j++)
		{
		    if(j%n==0)
                printf(" | ");

            if(grille[i][j]>taille)
                printf("%d ", grille[i][j]);
            else
                printf(" %d ", grille[i][j]);
		}
		printf("\n");

	}
	printf("\n\n");
}
