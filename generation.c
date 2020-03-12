#include <time.h>
#include "generation.h"
//#include "difficulte.h"

uint8_t** genererGrilleSudokuValide(size_t taille, int level)
{
    int difficulte = 0;
    srand(time(NULL));
    uint8_t ** grille = genererGrilleComplete(taille);
    //affichage(grille, taille);
    int casesRestante = taille*taille;
    retirerCaseRandom(grille, taille);
    casesRestante-=1;
    do
    {
        uint8_t ** grilleTemp = grille; // faire une de la grille copie;
		retirerCaseRandom(grilleTemp, taille);
		casesRestante-=1;
        difficulte = 1;
        //difficulte = validiterEtDifficulter(grilleTemp, taille, level);
        //La difficulté 5 permet a l'algorithme de renvoyer la derniere grille, car la nouvelle ne correspond plus au niveau souhaiter.
        //La difficulté 0 (erreur) ne remplace pas grille par grille_temp et permet donc de changer la case retirer aléatoirement.
        if (difficulte != 5 && difficulte != 0)
        {
            // libere la mémoire de la grille, et la remplace par la grille temporaire.
            grille = grilleTemp;
        }

        //si le nombre de cases restante est inferieur a 20, termine la boucle.
        if (casesRestante < 20)
        {
            difficulte = 5;
        }
    } while (difficulte != 5);

    return grille;
}

/*size_t retirerCaseRandomAvecCaseRestante(uint8_t **grille, size_t taille)
{
    size_t nbCases = 0;
    struct posCase *pos = malloc(taille * taille);
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            if (grille[i][j] != 0)
            {
                struct posCase temp = {i, j};
                pos[nbCases] = temp;
                nbCases++;
            }
        }
    }

    int aSuppr = rand() % nbCases;

    grille[pos[aSuppr].colonne][pos[aSuppr].ligne] = 0;

    return (nbCases - 1);
}*/

void retirerCaseRandom(uint8_t **grille, size_t taille)
{
    
    int reussi = 0;

    while (reussi == 0)
    {
    	size_t ligne = rand() % taille;
    	size_t colonne = rand() % taille;
        if (grille[colonne][ligne] != 0)
        {
            grille[colonne][ligne] = 0;
            reussi = 1;
        }
    }
}

uint8_t ** genererGrilleComplete(size_t taille)
{
    uint8_t ** retour = malloc(taille * sizeof(uint8_t*));
    for(int i = 0; i < taille; i++){
    	retour[i] = malloc(taille * sizeof(uint8_t));
    }
    size_t taille_bloc = (size_t)sqrt(taille);

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            //Formule pour generer, selon i, j,la taille de la grille, et taille_bloc la taille d'un bloc de la grille.
            //Genere une grille complete valide ayant pour premiere ligne {1,2,3,4,5,6,7,8,9}
            retour[i][j] = (((taille_bloc * i) + (((j + (i / taille_bloc)) % taille_bloc) + (taille_bloc * (j / taille_bloc)))) % (taille)) + 1;
        }
    }

    //Permutation / rotation

    for(int i = 0; i < taille*4; i++){
        int x = rand() % taille;
        int y = rand() % taille;
        while(x == y){
           y = rand() % taille;
        }
        permuterLignes(retour, taille);

        permuterColonnes(retour, taille);

        //retour = rotation(retour, taille);
    }
    return retour;
}

void permuterLignes(uint8_t **grille, size_t taille)
{
	size_t tailleBloc = sqrt(taille);
	//permutation des lignes d'une bande

    for(int i = 0; i < taille*taille; i++){
    	int v1 = (rand() %tailleBloc) + (tailleBloc*(i%tailleBloc));
    	int v2 = (rand() %tailleBloc) + (tailleBloc*(i%tailleBloc));
    	while(v1 == v2){
    		v2 = (rand() %tailleBloc) + (tailleBloc*(i%tailleBloc));
    	}
    	echangerLignes(grille, taille, v1, v2);
    }

    //permutation des bandes
    for(int i = 0; i < taille; i++){
    	int v1 = rand() %tailleBloc;
    	int v2 = rand() %tailleBloc;
    	while(v1 == v2){
    		v2 = rand() %tailleBloc;
    	}
    	echangerLignes(grille, taille, v1*tailleBloc, v2*tailleBloc);
    	echangerLignes(grille, taille, (v1*tailleBloc)+1, (v2*tailleBloc)+1);
    	echangerLignes(grille, taille, (v1*tailleBloc)+2, (v2*tailleBloc)+2);
    }

}

void permuterColonnes(uint8_t **grille, size_t taille)
{

	size_t tailleBloc = sqrt(taille);

	//permutation des colonne d'une pile
    for(int i = 0; i < taille*taille; i++){
    	int v1 = (rand() %tailleBloc) + (tailleBloc*(i%tailleBloc));
    	int v2 = (rand() %tailleBloc) + (tailleBloc*(i%tailleBloc));
    	while(v1 == v2){
    		v2 = (rand() %tailleBloc) + (tailleBloc*(i%tailleBloc));
    	}
    	echangerColonnes(grille, taille, v1, v2);
    }
    //permutation des piles
    for(int i = 0; i < taille; i++){
    	int v1 = rand() %tailleBloc;
    	int v2 = rand() %tailleBloc;
    	while(v1 == v2){
    		v2 = rand() %tailleBloc;
    	}
    	echangerColonnes(grille, taille, v1*tailleBloc, v2*tailleBloc);
    	echangerColonnes(grille, taille, (v1*tailleBloc)+1, (v2*tailleBloc)+1);
    	echangerColonnes(grille, taille, (v1*tailleBloc)+2, (v2*tailleBloc)+2);
    }
}

void echangerLignes(uint8_t ** grille, size_t taille, size_t ligne1, size_t ligne2){
	for (int i = 0; i < taille; i++)
    {
        int8_t temp = grille[i][ligne1];
        grille[i][ligne1] = grille[i][ligne2];
        grille[i][ligne2] = temp;
    }
}

void echangerColonnes(uint8_t ** grille, size_t taille, size_t colonne1, size_t colonne2){
	for (int i = 0; i < taille; i++)
    {
        int8_t temp = grille[colonne1][i];
        grille[colonne1][i] = grille[colonne2][i];
        grille[colonne2][i] = temp;
    }
}

void rotation(uint8_t **grille, size_t taille)
{
    //A FAIRE;
}

//pour debug
/*void affichage(uint8_t ** sudoku, size_t taille){
	printf("\n");
	for(int i = 0; i < taille; i++){
		for(int j = 0; j < taille; j++){
			if(sudoku[i][j] != 0){
				printf("| %i ", sudoku[i][j]);
			} else {
				printf("|   ");
			}
		}
		printf("|\n");
	}
}

int valide(uint8_t ** sudoku, size_t taille){
	int retour = 1;
	for(int i = 0; i < taille && retour == 1; i++){
		for(int j = 0; j < taille && retour == 1; j++){
			if(sudoku[i][j] != 0){
				retour = verif_lcz(sudoku, i, j, taille);
			}
		}
	}
}

int verif_lcz(uint8_t ** sudoku, int colonne, int ligne, size_t taille){
	int retour = 1;
	uint8_t val = sudoku[colonne][ligne];

	for(int i = 0; i < taille && retour == 1; i++){
		if( i != ligne){
			if(val == sudoku[colonne][i]){
				retour = 0;
				printf("LIGNE\n");
				printf("Erreur %ix%i : %i\n", colonne, ligne, val);
				printf("Avec   %ix%i : %i\n", colonne, i, sudoku[colonne][i]);
			}
		}
	}

	for(int i = 0; i < taille && retour == 1; i++){
		if( i != colonne){
			if(val == sudoku[i][ligne]){
				retour = 0;
				printf("COLONNE\n");
				printf("Erreur %ix%i : %i\n", colonne, ligne, val);
				printf("Avec   %ix%i : %i\n", i, ligne, sudoku[i][ligne]);
			}
		}
	}

	for(int i = 0; i < sqrt(taille) && retour == 1; i++){
		for(int j = 0; j < sqrt(taille) && retour == 1; j++){
			int nI = ((int) ( ((int) (colonne/sqrt(taille))) * sqrt(taille))) + i;
			int nJ = ((int) ( ((int) (ligne/sqrt(taille))) * sqrt(taille))) + j;

			if(nI != colonne && nJ != ligne){
				if(val == sudoku[nI][nJ]){
					retour = 0;
					printf("BLOC\n");
					printf("Erreur %ix%i : %i\n", colonne, ligne, val);
					printf("Avec   %ix%i : %i\n", i, j, sudoku[nI][nJ]);
				}
			}
		}	
	}
}*/