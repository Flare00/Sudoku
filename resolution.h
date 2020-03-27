#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "grille.h"
#include "liste.h"
#include "bitBoard.h"

#define bool uint8_t
#define true 1
#define false 0

/** @brief Ajouter un élément en tête de liste
  * @param Liste *liste : pointeur sur la liste à laquelle on rattachera une nouvelle
  * @param uint64_t candidats : entier représentant les candidats pour une case donnée
  * @param size_t i, j : coordonnée pour la case concernée
  * @return Liste* : la tête de la liste
  */
Liste* ajouterEnTete(Liste *liste, uint64_t candidats, size_t i, size_t j);
Liste32* ajouterEnTete32(Liste32 *liste, uint32_t candidats, size_t i, size_t j);

/** @brief Créer une liste pour les case à 1 élément
  * @param size_t n : la racine de la hauteur de la grille
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  * @return Liste* : la tête de la liste
  */
Liste* creerListeUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);
Liste32* creerListeUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille);

/** @brief Remplir directement les cases à 1 candidat
  * @param size_t n : la racine de la hauteur de la grille
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  */
void heuristiqueUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);
void heuristiqueUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille);

/** @brief Heuristique de résolution basé sur la technique de paire cachée, si 2 cases contiennent la même paire de valeur, on peut
  * @param size_t taille : nombre de valeurs par régions
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
  */
void heuristiquePaireCachee(size_t taille,Liste *dl,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t**map);
void heuristiquePaireCachee32(size_t taille,Liste32 *dl,uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t**map);

/** @brief Vérifie si la grille est résolu
  * @param uint8_t** grille : pointeur sur la grille
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
  * @return bool : true si la grille est résolu, false sinon
  */
bool resoudreRecursivement(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map);
bool resoudreRecursivement32(uint8_t** grille, Liste32 *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t **map);

/** @brief Résoudre la grille
  * @param uint8_t* entree : les informations de la grille ligne par ligne
  * @param size_t n : la racine de la taille de la grille
  * @return bool : true si le problème est résolu, false sinon
  */
bool resoudre(uint8_t *entree, size_t n);

#endif
