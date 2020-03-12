#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "grille.h"
#include "liste.h"
#include "bitBoard.h"
#include <math.h>
#define bool uint8_t
#define true 1;
#define false 0;




Liste* adjonctionEnTete(Liste *liste, uint64_t candidats, size_t i, size_t j);
Liste* creerListeUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);
void heuristiqueUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);
void heuristiqueEnsembleCache(size_t taille,Liste *dl,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t**map);

/** @brief Vérifie si la grille est résolu
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : bitBoard ligne
  * @param uint64_t* bbC : bitBoard colonne
  * @param uint64_t* bbB : bitBoard block
  * @param uint8_t** grille : pointeur sur la grille
  * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
  */
bool resolutionRecursive(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map);

#endif
