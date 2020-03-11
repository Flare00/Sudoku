#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "liste.h"
#include "grille.h"

/** @brief Creer un tableau de bits à partir d'une grille
  * @param uint8_t **grille : grille utilisée pour remplir le tableau de bits
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block*/
void initialiserBitBoard(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB);

/** @brief Destruction d'un tableau de bits
  * @param uint64_t** bb : tableau de bits à détruire*/
void detruireBitBoard(uint64_t *bb);

void afficherBit(uint64_t candidat, size_t taille);

void afficherBit_64(uint64_t candidat);

void afficherBitBoard(size_t taille, uint64_t* bb);

/** @brief Liste de candidats pour les cases vides
  * @param uint8_t **grille : grille utilisée pour remplir le tableau de bits
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau permettant de savoir les indices de block pour le tableau de bit.
  * @return Liste* : le pointeur  sur la liste de candidat(s) solo
  */
Liste* rechercheCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);

#endif
