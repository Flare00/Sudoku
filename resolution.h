#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "grille.h"
#include "liste.h"
#include "bitBoard.h"
#include <math.h>
#define bool uint8_t
#define true 1;
#define false 0;



/** @brief Ajoute une case avec un unique candidat en tête de liste.
  * @param Liste* : la liste des cellules qui n'ont qu'un seul candidat
  * @param uint64_t candidats : un entier non signé qui n'a qu'un seul bit à 1
  * @param size_t i: l'indice des lignes
  * @param size_t j: l'indice des colonnes
  * @return Liste* : la liste des cellules qui n'ont qu'un seul candidat
  */
Liste* adjonctionEnTete(Liste *liste, uint64_t candidats, size_t i, size_t j);

/** @brief Crée une liste des candidats unique
  * @param size_t n
  * @param uint64_t* bbL : bitBoard ligne
  * @param uint64_t* bbC : bitBoard colonne
  * @param uint64_t* bbB : bitBoard block
  * @param uint8_t** grille : pointeur sur la grille
  * @return Liste* : la liste des cellules qui n'ont qu'un seul candidat
  */
Liste* creerListeUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);


/** @brief Heuristique de résolution basé sur la technique du candidat unique, il est unique donc on le place directement.
  * @param size_t n
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : bitBoard ligne
  * @param uint64_t* bbC : bitBoard colonne
  * @param uint64_t* bbB : bitBoard block
  * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
  */
void heuristiqueUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);

/** @brief Heuristique de résolution basé sur la technique de paire cachée, si 2 cases contiennent la même paire de valeur, on peut supprimer la paire dans les autres régions.
  * @param size_t taille
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : bitBoard ligne
  * @param uint64_t* bbC : bitBoard colonne
  * @param uint64_t* bbB : bitBoard block
  * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
  */
void heuristiquePaireCachee(size_t taille,Liste *dl,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t**map);

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
