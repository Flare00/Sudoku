#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "liste.h"
#include "grille.h"


/** @brief Creer un tableau de bits à partir d'une grille
  * @param uint8_t **grille : grille utilisée pour remplir le tableau de bits
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block*/
void bitBoardInitialiser(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB);

/** @brief Destruction d'un tableau de bits
  * @param uint64_t** bb : tableau de bits à détruire*/
void bitBoardDetruire(uint64_t *bb);

/** @brief Initialiser un tableau de bits sur 4 octets
  * @param size_t taille : espace nécessaire à l'initialisation
  * @return uint32_t* : pointeur sur un tableau de bits*/
uint32_t* bitboard32Creer(size_t taille);

/** @brief Initialiser un tableau de bits sur 8 octets
  * @param size_t taille : espace nécessaire à l'initialisation
  * @return uint64_t* : pointeur sur un tableau de bits*/
uint64_t* bitboard64Creer(size_t taille);

/** @brief Affichage d'un entier dont on connaît la taille
  * @param uint64_t candidats : l'entier non signé qui contient les candidats
  * @param size_t taille : taille des bits pertinents
  */
void afficherBit(uint64_t candidat, size_t taille);

/** @brief Affichage d'un entier 64 bits
  */
void afficherBit_64(uint64_t candidat);

/** @brief Affichage d'un plateau de bit
  * @param size_t taille : taille du plateau
  * @param uint64_t* bb : tableau de bits du plateau
  */
void afficherBitBoard(size_t taille, uint64_t* bb);

/** @brief Affichage de tous les plateau de bit ligne, colonne et block
  * @param size_t taille : taille du plateau
  * @param uint64_t* bbL : tableau de bits du plateau ligne
  * @param uint64_t* bbC : tableau de bits du plateau colonne
  * @param uint64_t* bbB : tableau de bits du plateau block
  */
void afficherTousBitBoard(size_t taille,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB);

#endif
