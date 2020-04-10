#ifndef __HEURISTIQUE_H__
#define __HEURISTIQUE_H__

#include <stdint.h>

/**
 * @brief execute toutes les heuristique de niveau Facile.
 * @param uint8_t** grille : pointeur sur la grille
 * @param uint64_t* bbL : tableau de bits ligne
 * @param uint64_t* bbC : tableau de bits colonne
 * @param uint64_t* bbB : tableau de bits block
 * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
 * @return nombre de cases restantes à remplir.
 */
size_t heuristiqueFacile(uint8_t ** grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);

/**
 * @brief execute toutes les heuristique de niveau Moyen, plus les heuristique de niveau Facile.
 * @param uint8_t** grille : pointeur sur la grille
 * @param uint64_t* bbL : tableau de bits ligne
 * @param uint64_t* bbC : tableau de bits colonne
 * @param uint64_t* bbB : tableau de bits block
 * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
 * @return nombre de cases restantes à remplir.
 */
size_t heuristiqueMoyenne(uint8_t ** grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);

/**
 * @brief execute toutes les heuristique de niveau Difficile, plus les heuristiques de niveau Moyen et Facile.
 * @param uint8_t** grille : pointeur sur la grille
 * @param uint64_t* bbL : tableau de bits ligne
 * @param uint64_t* bbC : tableau de bits colonne
 * @param uint64_t* bbB : tableau de bits block
 * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
 * @return nombre de cases restantes à remplir.
 */
size_t heuristiqueDifficile(uint8_t ** grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);

//Niveau Facile
void heuristiqueSingleton(uint8_t ** grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);

//Niveau Moyen
/**
 * @brief fonction heuristique permettant d'effectuer la technique de Jumeau, Triple, et N Visible. 
 * 
 * Si dans une région R de largeur N, un candidats C est présent entre 2 et N fois, et strictement aligné sur une ligne ou une colonne, 
 * alors pour le reste de la ligne/colonne, C ne peut pas être présent, et nous pouvons  donc supprimé ses occurrences.
 * https://www.mots-croises.ch/Manuels/Sudoku/jumeaux.htm
 * 
 * @param uint8_t** grille : pointeur sur la grille
 * @param uint64_t* bbL : tableau de bits ligne
 * @param uint64_t* bbC : tableau de bits colonne
 * @param uint64_t* bbB : tableau de bits block
 * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueJumeauANVisible(uint8_t ** grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);

/**
 * @brief fonction heuristique permettant d'effectuer la technique de Candidats Identiques
 * 
 * Si pour une même ligne/colonne, un groupe de N candidats C, se présente N fois, sur N régions strictement différentes,
 * nous pouvons supprimé de la ligne/colonne toute occurrences de C, sauf dans les cases d’origine.
 * https://www.mots-croises.ch/Manuels/Sudoku/candidats_identiques.htm
 * 
 * @param uint8_t** grille : pointeur sur la grille
 * @param uint64_t* bbL : tableau de bits ligne
 * @param uint64_t* bbC : tableau de bits colonne
 * @param uint64_t* bbB : tableau de bits block
 * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueCandidatsIdentique(uint8_t ** grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);

//Niveau Difficile

/**
 * @brief fonction heuristique permettant d'effectuer la technique de Groupes Isolés
 * 
 * Si pour une même ligne/colonne, N groupe de M candidats C (strictement identique ou identique avec candidats manquant) (M compris entre 2 et N),
 * dont 1 contient les N candidats, sur N cases de la ligne/colonne, alors ces candidats ne peuvent pas être présent sur les autres cases de la ligne/colonne.
 * https://www.mots-croises.ch/Manuels/Sudoku/groupes_isoles.htm
 * 
 * @param uint8_t** grille : pointeur sur la grille
 * @param uint64_t* bbL : tableau de bits ligne
 * @param uint64_t* bbC : tableau de bits colonne
 * @param uint64_t* bbB : tableau de bits block
 * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueGroupesIsoler(uint8_t ** grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);

/**
 * @brief fonction heuristique permettant d'effectuer la technique de Groupes Mélangés
 * 
 * Si pour une même ligne/colonne, N groupe de X candidats contiennent un sous groupe de M candidats C (strictement identique ou identique avec candidats manquant)
 * (M compris entre 2 et N) dont au moins 1 contient tout les candidats, sur N cases de la ligne/colonne, alors tout autre candidats de leurs cases peuvent être retirer.
 * https://www.mots-croises.ch/Manuels/Sudoku/groupes_melanges.htm
 * 
 * @param uint8_t** grille : pointeur sur la grille
 * @param uint64_t* bbL : tableau de bits ligne
 * @param uint64_t* bbC : tableau de bits colonne
 * @param uint64_t* bbB : tableau de bits block
 * @param uint8_t** map : tableau contenant les indices de région pour le tableau de bits block (bbB)
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueGroupesMelanger(uint8_t ** grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);



#endif
