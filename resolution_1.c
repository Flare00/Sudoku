#include "resolution_1.h"

int8_t **creer_grille(char *chaine, size_t hauteur)
{
	int8_t **grille = malloc(hauteur * sizeof(int8_t*));
	assert(grille != NULL);

	for (size_t i = 0; i < hauteur; i++)
	{
		grille[i] = malloc(hauteur * sizeof(int8_t));
		assert(grille[i] != NULL);

		size_t x = i*hauteur;
		for (size_t j = 0; j < hauteur; j++)
		{
			int8_t c = chaine[x+j];
			if(c>=48 && c<=57) // ['0';'9']
				grille[i][j] = c-48;
			else if(c>=65 && c<=90) // ['A';'Z']
				grille[i][j] = c-55;
			else if(c>=97 && c<=122) // ['a';'z']
				grille[i][j] = c-61;
			else if(c>=62 && c<= 64) // {'>' ; '?' ; '@'}
				grille[i][j] = c;
			else
			{
				fprintf(stderr, "Modifiez le n du main ou la chaine utilisée pour la crétion de la grille\n");
				exit(1);
			}
		}
	}

	return grille;
}

void detruire_grille(int8_t **grille, size_t hauteur)
{
	for (size_t i = 0; i < hauteur; i++)
	{
		free(grille[i]);
	}
	free(grille);
}

void afficherGrille(size_t hauteur, int8_t **grille)
{
	printf("\n\nGrille : \n");
	for(size_t i = 0; i < hauteur; i++)
	{
		for(size_t j = 0; j < hauteur; j++)
		{
			//pour ne voir que les nombres
			//printf((grille[i][j] < 10) ? "%d  " : "%d ", grille[i][j]);
			if(grille[i][j] < 10)
				printf("%d ", grille[i][j]);
			else if(grille[i][j]>=62 && grille[i][j]<= 64)
				printf("%c ", grille[i][j]);
			else if(grille[i][j]<=90)
				printf("%c ", grille[i][j]+55);
			else if(grille[i][j]<=122)
				printf("%c ", grille[i][j]+61);
		}
		printf("\n");
	}
	printf("\n");
	return;
}