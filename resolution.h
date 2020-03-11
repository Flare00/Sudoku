#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "grille.h"
#include "liste.h"
#include "bitBoard.h"

#define bool uint8_t
#define true 1;
#define false 0;
#define block(a, b,n)    (((a/n)*n)+b/n)

uint8_t** creerMap(size_t n);

void detruireMap(uint8_t **map, size_t taille);

/** @brief Renvoie vrai si un élément peut re inséré dans une case en modifiant le tableau de bit, 
	faux sinon
  * @param uint64_t* bbL : bitBoard ligne
  * @param uint64_t* bbC : bitBoard colonne
  * @param uint64_t* bbB : bitBoard block
  * @param uint64_t candidats : les candidats de l'élément à insérer
  * @param uint64_t mask : */
bool insertionValide(uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint64_t candidat, uint64_t mask);

/** @brief Ajoute un élément en tête de liste
  * @param Liste *dl :un pointeur sur une liste
  * @param uint64_t candidats : les candidats de l'élément à insérer
  * @param  size_t i, size_t j : la position dans la grille
  * @return Liste* : le pointeur sur le nouvel élément ajouté
  */
void iterativeResolution(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map, Liste** l1);

/** @brief Ajoute un élément en tête de liste
  * @param Liste *dl :un pointeur sur une liste
  * @param uint64_t candidats : les candidats de l'élément à insérer
  * @param  size_t i, size_t j : la position dans la grille
  * @return Liste* : le pointeur sur le nouvel élément ajouté
  */
bool resolu(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map);


#endif
