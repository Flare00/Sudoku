#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "bitBoard.h"

/** @brief Ajouter un �l�ment en t�te de liste
  * @param Liste *liste : pointeur sur la liste � laquelle on rattachera une nouvelle
  * @param uint64_t candidats : entier repr�sentant les candidats pour une case donn�e
  * @param size_t i, j : coordonn�e pour la case concern�e
  * @return Liste* : la t�te de la liste
  */
Liste* ajouterEnTete(Liste *liste, uint64_t candidats, size_t i, size_t j);
Liste32* ajouterEnTete32(Liste32 *liste, uint32_t candidats, size_t i, size_t j);

/** @brief Cr�er une liste pour les case � 1 �l�ment
  * @param size_t n : la racine de la hauteur de la grille
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  * @return Liste* : la t�te de la liste
  */
Liste* creerListeUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);
Liste32* creerListeUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map);

/** @brief Remplir directement les cases � 1 candidat
  * @param size_t n : la racine de la hauteur de la grille
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  */
void heuristiqueUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);
void heuristiqueUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map);

/** @brief Heuristique de r�solution bas� sur la technique de paire cach�e, si 2 cases contiennent la m�me paire de valeur, on peut
  * @param size_t taille : nombre de valeurs par r�gions
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  * @param uint8_t** map : tableau contenant les indices de r�gion pour le tableau de bits block (bbB)
  */
void heuristiquePaireCachee(size_t taille,Liste *dl,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t**map);
void heuristiquePaireCachee32(size_t taille,Liste32 *dl,uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t**map);

/** @brief V�rifie si la grille est r�solu
  * @param uint8_t** grille : pointeur sur la grille
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau contenant les indices de r�gion pour le tableau de bits block (bbB)
  * @return bool : true si la grille est r�solu, false sinon
  */
bool resoudreRecursivement(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map);
bool resoudreRecursivement32(uint8_t** grille, Liste32 *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t **map);

/** @brief V�rifie si la grille est r�solu et renvoie le nombre de solution � tester ensuite
  * @param uint8_t** grille : pointeur sur la grille
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau contenant les indices de r�gion pour le tableau de bits block (bbB)
  * @param int pi,pj : index de la premi�re case de la liste
  * @param int count : compteur du nombre de solutions
  * @return int: nombre de solution 0, 1 ou 2
  */


/** @brief V�rifie si la grille est r�solu et renvoie le nombre de solution � tester ensuite
  * @param uint8_t** grille : pointeur sur la grille
  * @param Liste *dl : pointeur sur une liste
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau contenant les indices de r�gion pour le tableau de bits block (bbB)
  * @param int pi,pj : index de la premi�re case de la liste
  * @param int count : compteur du nombre de solutions
  * @return int: nombre de solution 0, 1 ou 2
  */

int resolu_64(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map, int count, int pi, int pj);

int resolu_32(uint8_t** grille, Liste *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t **map, int count, int pi, int pj);

/** @brief R�soudre la grille
  * @param uint8_t* entree : les informations de la grille ligne par ligne
  * @param size_t n : la racine de la taille de la grille
  * @return bool : true si le probl�me est r�solu, false sinon
  */
bool resoudre(uint8_t *entree, size_t n);

#endif
