#ifndef BITBOARD_H
#define BITBOARD_H

#include "grille.h"
#include "liste.h"

/** @brief Créer un tableau de bits
  * @param size_t taille : espace nécessaire à l'initialisation
  * @return uint64_t* : pointeur sur un tableau de bits*/
uint64_t* bitboard64Creer(size_t taille);

/** @brief Créer un tableau de bits
  * @param size_t taille : espace nécessaire à l'initialisation
  * @return uint32_t* : pointeur sur un tableau de bits*/
uint32_t* bitboard32Creer(size_t taille);

/** @brief Détruire un tableau de bits de type uint64_t
  * @param uint64_t* bb : tableau de bits à détruire*/
void bitBoardDetruire(uint64_t *bb);

/** @brief Détruire un tableau de bits de type uint32_t
  * @param uint32_t* bb : tableau de bits à détruire*/
void bitBoardDetruire32(uint32_t *bb);

/** @brief Initialiser des tableaux de bits à partir d'une grille
  * @param uint8_t **grille : grille servant à l'initialisation
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block*/
bool bitBoardInitialiser(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB);

/** @brief Initialiser les tableaux de bits à partir d'une grille
  * @param uint8_t **grille : grille servant à l'initialisation
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block*/
bool bitBoardInitialiser32(uint8_t **grille, size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB);

/** @brief Afficher les candidats sous forme de bits
  * @param uint64_t candidats : l'entier non signé qui contient les candidats
  * @param size_t taille : les tailles bits à afficher
  */
void bitAfficher(uint64_t candidats, size_t taille);

/** @brief Afficher les candidats sous forme de bits
  * @param uint32_t candidats : l'entier non signé qui contient les candidats
  * @param size_t taille : les tailles bits à afficher
  */
void bitAfficher32(uint32_t candidats, size_t taille);

/** @brief Afficher un tableau de bits
  * @param size_t taille : taille de bb
  * @param uint64_t* bb : tableau de bits à afficher
  */
void bitBoardAfficher(size_t taille, uint64_t* bb);

/** @brief Afficher un tableau de bits
  * @param size_t taille : taille de bb
  * @param uint32_t* bb : tableau de bits à afficher
  */
void bitBoardAfficher32(size_t taille, uint32_t* bb);

/** @brief Afficher tous les tableaux de bit ligne, colonne et block
  * @param size_t taille : taille du tableau
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  */
void bitBoardAfficherTout(size_t taille, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB);

/** @brief Afficher tous les tableaux de bit ligne, colonne et block
  * @param size_t taille : taille du tableau
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block
  */
void bitBoardAfficherTout32(size_t taille, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB);

#endif
