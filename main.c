#include "doc.h"
#include "grille.h"
#include "bitBoard.h"
#include "liste.h"


int main(int argc, char *argv[]){
	size_t n = 3;
	size_t taille = n*n;
    unsigned int entree[81] = {0,2,0,3,1,7,0,0,0,0,0,0,0,0,9,8,2,1,5,4,0,0,0,0,0,3,0,0,0,9,0,6,2,4,0,3,0,0,0,1,3,0,0,0,6,0,0,7,0,8,4,1,0,2,8,1,0,0,0,0,0,7,0,0,0,0,0,0,1,2,4,8,0,6,0,4,7,8,0,0,0};

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
	res(taille,n,bbL,bbC,bbB,grille,&liste);
	printf("\nNUMERO DOS\n\n");
	afficherListe(liste);
	afficherGrille(taille, n, grille);

	detruireGrille(grille, taille);
	detruireBitBoard(bbL);
	detruireBitBoard(bbC);
	detruireBitBoard(bbB);
	detruireListe(liste);

	return 0;
}
