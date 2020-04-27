#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "bitBoard.h"

/** @brief Placer chaque candidats de la liste dans la grille
  * @param size_t n : le nombre de cases par ligne ou colonne de block
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  */
void heuristiqueUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);

/** @brief Placer chaque candidats de la liste dans la grille
  * @param size_t n : le nombre de cases par ligne ou colonne de block
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  */
void heuristiqueUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map);

/** @brief Pour deux cases de la même ligne, du même block ou de la même colonne portant exactement
    2 candidats identiques, on supprime ces deux candidats de la ligne, la colonne ou du block partagé(e)
  * @param size_t taille : nombre de cases par ligne, colonne ou block
  * @param Liste *dl : pointeur sur une liste
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  * @param uint8_t** map : tableau contenant les indices de block pour le tableau de bits block (bbB)
  */
void heuristiquePaireCachee(size_t taille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t**map);

/** @brief Pour deux cases de la même ligne, du même block ou de la même colonne portant exactement
    2 candidats identiques, on supprime ces deux candidats de la ligne, la colonne ou du block partagé(e)
  * @param size_t taille : nombre de cases par ligne, colonne ou block
  * @param Liste32 *dl : pointeur sur une liste
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  * @param uint8_t** map : tableau contenant les indices de block pour le tableau de bits block (bbB)
  */
void heuristiquePaireCachee32(size_t taille, Liste32 *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t**map);

/** @brief Placer les éléments de la liste à 1 candidat dans la grille
  * @param Liste **liste : pointeur sur l'adresse de la liste
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau contenant les indices de block pour le tableau de bits block (bbB)
  * @param uint8_t **grille : pointeur sur la grille
  * @return bool : true si l'heuristique a pu être appliquer, false sinon.
  */
bool heuristiqueSolo(Liste **liste, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map, uint8_t **grille);

/** @brief Placer les éléments de la liste à 1 candidat dans la grille
  * @param Liste32 **liste : pointeur sur l'adresse de la liste
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau contenant les indices de block pour le tableau de bits block (bbB)
  * @param uint8_t **grille : pointeur sur la grille
  * @return bool : true si l'heuristique a pu être appliquer, false sinon.
  */
bool heuristiqueSolo32(Liste32 **liste, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t **map, uint8_t **grille);

/** @brief Pour deux éléments de la liste de population 2 et de même candidats, on supprime de la liste les autres éléments
  de même ligne, colonne ou bloc chacun des candidats s'ils y sont.
  * @param Liste **liste : pointeur sur l'adresse de la liste
  * @param uint8_t** map : tableau contenant les indices de block savoir si deux cases partagent le même bloc
  * @return bool : true si l'heuristique a pu être appliquer, false sinon.
  */
bool heuristiquePaireNue(Liste **liste, uint8_t **map);

/** @brief Pour deux éléments de la liste de population 2 et de même candidats, on supprime de la liste les autres éléments
  de même ligne, colonne ou bloc chacun des candidats s'ils y sont.
  * @param Liste32 **liste : pointeur sur l'adresse de la liste
  * @param uint8_t** map : tableau contenant les indices de block pour le tableau de bits block (bbB)
  * @return bool : true si l'heuristique a pu être appliquer, false sinon.
  */
bool heuristiquePaireNue32(Liste32 **liste, uint8_t **map);

/** @brief Application du backtracking
  * @param uint8_t** grille : pointeur sur la grille
  * @param Liste *dl : pointeur sur une liste de candidats
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau contenant les indices de block pour le tableau de bits block (bbB)
  * @return bool : true si la grille est résolu, false sinon
  */
bool resoudreRecursivement(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);

/** @brief Application du backtracking
  * @param uint8_t** grille : pointeur sur la grille
  * @param Liste *dl : pointeur sur une liste de candidats
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau contenant les indices de block pour le tableau de bits block (bbB)
  * @return bool : true si la grille est résolu, false sinon
  */
bool resoudreRecursivement32(uint8_t** grille, Liste32 *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t **map);

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
int resolu_64(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map, int count, int pi, int pj);

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
int resolu_32(uint8_t** grille, Liste *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t **map, int count, int pi, int pj);

/** @brief Fonction liée à l'interface graphique qui permet de résoudre la grille sur 32/64 bits selon de sa dimension (n*n)
  * @param uint8_t* entree : les informations de la grille ligne par ligne
  * @param size_t n : la racine de la taille de la grille
  * @return bool : true si le probl�me est r�solu, false sinon
  */
bool resoudre(uint8_t *entree, size_t n);

#endif
