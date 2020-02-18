#include "doc.h"
#include "resolution.h"


int main(int argc, char *argv[]){

	/*int8_t sudoku_ex_mat[9][9]={{0,2,0,3,1,7,0,0,0,
								{0,0,0,0,0,9,8,2,1,
								{5,4,0,0,0,0,0,3,0,
								{0,0,9,0,6,2,4,0,3,
								{0,0,0,1,3,0,0,0,6},
								{0,0,7,0,8,4,1,0,2},
								{8,1,0,0,0,0,0,7,0},
								{0,0,0,0,0,1,2,4,8},
								{0,6,0,4,7,8,0,0,0}};*/
    unsigned int entree[81] = {0,2,0,3,1,7,0,0,0,0,0,0,0,0,9,8,2,1,5,4,0,0,0,0,0,3,0,0,0,9,0,6,2,4,0,3,0,0,0,1,3,0,0,0,6,0,0,7,0,8,4,1,0,2,8,1,0,0,0,0,0,7,0,0,0,0,0,0,1,2,4,8,0,6,0,4,7,8,0,0,0};
	size_t taille = DIMENSION*DIMENSION; /* Taille de la grille*/

	uint8_t** grille = (uint8_t **)creerGrille(entree, taille);

	afficherGrille(taille, grille);

	detruireGrille(grille, taille);

	return 0;
}
