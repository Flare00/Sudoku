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

// /** @brief Renvoie vrai si un élément peut re inséré dans une case en modifiant le tableau de bit, 
// 	faux sinon
//   * @param uint64_t* bbL : bitBoard ligne
//   * @param uint64_t* bbC : bitBoard colonne
//   * @param uint64_t* bbB : bitBoard block
//   * @param uint64_t candidats : les candidats de l'élément à insérer
//   * @param uint64_t mask : */
// bool insertionValide(uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint64_t candidat, uint64_t mask);

// * @brief Elimination de manières itérative de candidtas
//   * @param Liste** l1 : référence sur une liste
//   * @param size_t n : la racine de la hauteur de la grille
//   * @param uint64_t* bbL : bitBoard ligne
//   * @param uint64_t* bbC : bitBoard colonne
//   * @param uint64_t* bbB : bitBoard block
//   * @param uint8_t** grille : pointeur sur la grille
//   * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
  
// void iterativeResolution(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map, Liste **l1);

/** @brief Vérifie si la grille est résolu
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : bitBoard ligne
  * @param uint64_t* bbC : bitBoard colonne
  * @param uint64_t* bbB : bitBoard block
  * @param uint8_t** grille : pointeur sur la grille
  * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
  */
bool resolu(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map);


Liste* adjonctionEnTete(Liste *liste, uint64_t candidats, size_t i, size_t j);
Liste* resoBis(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);
void reso(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);

#endif
