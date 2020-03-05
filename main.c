#include "doc.h"
#include "grille.h"
#include "bitBoard.h"
#include "liste.h"
#include "resolution.h"

int main(int argc, char **argv)
{
	size_t n = 4;
	size_t taille = n*n;
    unsigned int entree[81] = {0,2,0,3,1,7,0,0,0,0,0,0,0,0,9,8,2,1,5,4,0,0,0,0,0,3,0,0,0,9,0,6,2,4,0,3,0,0,0,1,3,0,0,0,6,0,0,7,0,8,4,1,0,2,8,1,0,0,0,0,0,7,0,0,0,0,0,0,1,2,4,8,0,6,0,4,7,8,0,0,0};

    //unsigned int entree[256] = {0,0,0,0,0,0,7,8,0,10,11,12,13,0,0,16,0,0,7,8,1,2,3,4,13,0,0,16,0,10,11,12,0,10,11,0,0,0,0,16,1,2,3,4,0,0,7,8,13,0,0,16,0,10,11,12,0,0,7,8,1,2,3,4,0,0,4,3,6,5,8,7,10,0,12,11,14,13,16,15,6,5,8,7,0,0,4,0,0,0,0,0,10,0,12,11,10,0,0,0,0,0,0,15,0,0,4,3,6,5,8,7,14,13,16,15,10,0,12,11,6,5,8,7,0,0,4,3,3,4,1,2,7,8,0,0,11,12,0,10,0,0,0,0,7,8,0,0,3,4,1,2,15,16,13,14,11,12,0,10,11,12,0,10,15,16,13,14,3,4,1,2,7,8,0,0,15,16,13,14,11,12,0,10,7,8,0,0,3,4,1,2,4,3,0,0,8,7,6,5,0,0,0,0,0,0,0,0,8,7,6,5,4,3,0,0,16,15,14,13,12,11,10,0,0,0};


	uint8_t **grille = creerGrille(entree, taille);

	printf("\nGrille : \n");
	afficherGrille(taille, n, grille);

	uint64_t* bbL = malloc(taille * sizeof(uint64_t));
	assert(bbL != NULL);
	uint64_t* bbC = malloc(taille * sizeof(uint64_t));
	assert(bbC != NULL);
	uint64_t* bbB = malloc(taille * sizeof(uint64_t));
	assert(bbB != NULL);

	initialiserBitBoard(grille, taille, n, bbL, bbC, bbB);

	printf("\nBitBoard ligne : \n");
	afficherBitBoard(taille, bbL);

	printf("\nBitBoard colonne : \n");
	afficherBitBoard(taille, bbC);

	printf("\nBitBoard block : \n");
	afficherBitBoard(taille, bbB);

	Liste *liste = rechercheCandidat(taille, n, bbL, bbC, bbB, grille);

	afficherListe(liste);

	if(resolu(grille, liste, taille, n, bbL, bbC, bbB))
	{
		afficherGrille(taille, n, grille);
	}
	else printf("Erreur de résolution !\n");

	detruireGrille(grille, taille);
	detruireBitBoard(bbL);
	detruireBitBoard(bbC);
	detruireBitBoard(bbB);
	detruireListe(liste);

	return 0;
}