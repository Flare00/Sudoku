#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "liste.h"
#include "grille.h"

/** @brief Creer un bitBoard à partir d'une grille
  * @param uint8_t **grille : grille utilisée pour remplir le bitBoard
  * @param size_t taille : nombre de case par ligne ou colonne de la grille
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint64_t* bbL : bitBoard ligne
  * @param uint64_t* bbC : bitBoard colonne
  * @param uint64_t* bbB : bitBoard block*/
void initialiserBitBoard(uint8_t **grille, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB);

/** @brief Destruction d'un bitBoard
  * @param uint64_t** bb : bitBoard à détruire*/
void detruireBitBoard(uint64_t *bb);

void afficherBit(uint64_t candidat, size_t taille);
void afficherBit_64(uint64_t candidat);

void afficherBitBoard(size_t taille, uint64_t* bb);

Liste* rechercheCandidat(size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);


#endif
