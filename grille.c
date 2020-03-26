#include "grille.h"

uint8_t **grilleCreer(uint8_t *chaine, size_t taille)
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
                grilleDetruire(grille, i);
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

void grilleDetruire(uint8_t **grille, size_t taille)
{
	for (size_t i = 0; i < taille; i++)
	{
		free(grille[i]);
	}
	free(grille);
}

void afficherGrille(size_t taille, size_t n, uint8_t **grille)
{
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

            if(grille[i][j]>9)
                printf("%d ", grille[i][j]);
            else
                printf(" %d ", grille[i][j]);
		}
		printf("\n");

	}
	printf("\n");
}

uint8_t** mapCreer(size_t n)
{
    size_t taille = n*n;
    uint8_t **map = malloc(taille * sizeof(uint8_t*));
    if(!map) return NULL;
    for (size_t i = 0; i < taille; i++)
    {
        map[i] = malloc(taille * sizeof(uint8_t));
        if(!map[i])
        {
            grilleDetruire(map, i); //puisque map est de la même dimension que grille, on peut utiliser grilleDetruire
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

void mapDetruire(uint8_t **map, size_t taille)
{
    for (int i = 0; i < taille; ++i)
    {
        free(map[i]);
    }
    free(map);
}
