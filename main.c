#include "doc.h"
#include "grille.h"
#include "bitBoard.h"
#include "liste.h"
#include "resolution.h"
#include <time.h>

int main(int argc, char **argv)
{
	size_t n = 5;
	size_t taille = n*n;
    //unsigned int entree[81] = {0,2,0,3,1,7,0,0,0,0,0,0,0,0,9,8,2,1,5,4,0,0,0,0,0,3,0,0,0,9,0,6,2,4,0,3,0,0,0,1,3,0,0,0,6,0,0,7,0,8,4,1,0,2,8,1,0,0,0,0,0,7,0,0,0,0,0,0,1,2,4,8,0,6,0,4,7,8,0,0,0};

    //unsigned int entree[256] = {0,0,0,0,0,0,7,8,0,10,11,12,13,0,0,16,0,0,7,8,1,2,3,4,13,0,0,16,0,10,11,12,0,10,11,0,0,0,0,16,1,2,3,4,0,0,7,8,13,0,0,16,0,10,11,12,0,0,7,8,1,2,3,4,0,0,4,3,6,5,8,7,10,0,12,11,14,13,16,15,6,5,8,7,0,0,4,0,0,0,0,0,10,0,12,11,10,0,0,0,0,0,0,15,0,0,4,3,6,5,8,7,14,13,16,15,10,0,12,11,6,5,8,7,0,0,4,3,3,4,1,2,7,8,0,0,11,12,0,10,0,0,0,0,7,8,0,0,3,4,1,2,15,16,13,14,11,12,0,10,11,12,0,10,15,16,13,14,3,4,1,2,7,8,0,0,15,16,13,14,11,12,0,10,7,8,0,0,3,4,1,2,4,3,0,0,8,7,6,5,0,0,0,0,0,0,0,0,8,7,6,5,4,3,0,0,16,15,14,13,12,11,10,0,0,0};

	unsigned int entree[625] ={0,0,1,0,0,24,0,0,15,0,0,18,17,0,0,0,0,0,0,13,0,14,0,20,21,0,0,9,0,0,0,0,0,13,6,4,0,0,2,0,0,24,0,17,0,0,0,5,3,7,0,21,19,0,0,0,0,12,20,11,0,0,0,7,0,25,4,8,0,16,0,2,22,24,0,0,24,0,14,5,0,7,0,0,0,8,0,12,0,0,0,0,20,0,18,25,0,0,13,0,0,20,0,0,22,23,2,0,25,19,6,3,0,0,0,0,12,0,7,0,4,10,16,0,0,9,5,0,0,18,0,0,0,0,0,16,2,3,20,0,0,15,25,21,23,24,0,0,19,0,16,22,25,0,0,7,0,0,0,9,21,0,0,6,12,0,3,0,0,0,8,0,0,0,0,0,15,2,0,0,14,0,0,10,0,22,0,24,18,0,19,0,0,8,4,12,20,0,21,0,0,0,0,0,3,0,22,4,0,1,13,0,0,0,17,0,2,18,20,0,16,0,0,0,15,4,0,0,0,0,0,0,0,17,0,5,0,1,8,0,12,0,6,0,9,14,0,3,0,23,5,0,0,6,0,20,17,0,0,0,0,19,22,0,0,0,0,0,10,12,9,0,21,15,0,0,0,0,0,0,10,0,0,0,0,0,16,0,1,0,0,0,11,0,0,13,8,0,14,0,20,0,0,0,25,8,0,0,0,0,15,0,23,0,7,0,0,0,19,0,3,0,10,0,6,0,14,11,0,9,0,3,25,6,21,20,0,18,0,0,0,0,0,5,15,0,0,1,0,16,0,0,0,0,0,11,0,0,0,0,10,17,0,0,0,2,1,9,0,8,22,5,24,0,0,25,0,0,0,8,0,0,0,0,0,12,6,0,23,13,0,10,1,0,0,0,18,11,5,24,0,0,0,0,4,0,0,0,0,0,0,22,19,0,14,0,0,0,0,0,0,0,23,12,0,15,10,6,12,19,4,0,0,0,2,0,0,0,0,9,0,23,0,0,3,0,0,0,0,0,0,0,22,0,0,1,18,20,0,8,0,0,0,16,3,6,0,0,25,0,7,0,9,0,0,11,1,0,13,20,0,0,6,9,3,2,7,0,0,4,5,0,19,0,21,10,0,0,22,25,0,0,0,23,0,12,0,0,11,0,0,0,0,5,20,8,17,0,24,0,0,0,25,0,0,0,8,5,0,17,18,10,0,3,0,7,15,0,0,0,11,21,23,0,0,0,0,0,4,22,14,0,12,16,10,0,0,1,0,0,0,0,2,17,0,0,0,7,15,0,0,0,8,6,0,7,6,20,0,0,0,24,13,8,0,0,0,0,4,0,0,18,22,0,5,1,15,0,2,17,18,0,0,0,0,25,16,0,14,0,0,0,6,0,0,0,0,3,0,10,5,0,0,0,12};

   /*unsigned int entree[625];
	for(int k =0; k<625;k++)
        entree[k]=0;*/

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
	time_t begin = time( NULL );

	//printf("\ncandidat en moyenne : %ld \n", nbCandidatListe(liste));
    res(taille,n, bbL, bbC, bbB, grille, &liste);

	printf("\nBitBoard ligne : \n");
	afficherBitBoard(taille, bbL);

	printf("\nBitBoard colonne : \n");
	afficherBitBoard(taille, bbC);

	printf("\nBitBoard block : \n");
	afficherBitBoard(taille, bbB);
	afficherGrille(taille, n, grille);
	printf("candidat en moyenne : %ld \n", nbCandidatListe(liste));

	if(resolu(grille, liste, taille, n, bbL, bbC, bbB))
	{
		afficherGrille(taille, n, grille);
	}
	else printf("Erreur de résolution !\n");


	time_t end = time( NULL);

	unsigned long secondes = (unsigned long) difftime( end, begin );
    printf( "Finished in %ld sec\n", secondes );

	detruireGrille(grille, taille);
	detruireBitBoard(bbL);
	detruireBitBoard(bbC);
	detruireBitBoard(bbB);
	detruireListe(liste);

	return 0;
}
