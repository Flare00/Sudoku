#ifndef __DIFFICULTE_H__
#define __DIFFICULTE_H__

#include <stdint.h>
#include <math.h>
#include "bitBoard.h"
#include "liste.h"
#include "heuristique.h"
#include "resolution.h"

/**
* \file difficulte.h
*
* Liste des différente technique par niveau de difficulté :
* Facile : 	- Singleton direct
*			- Singleton caché
*			
*
* Moyen : 	- Sujet disjoints
*			- Jumeau/Triplé visible
*			- Candidats identiques
* 
* Difficle: - Chaine disjointe
*			- Jumeau/Triplé caché
*			- Groupe isolé
*			- Groupes mélangés
*
* Expert :  - X-Wing
*			- Swordfish
*			- etc...
*/

/**
* \brief fonction qui permet de determiner la validité et la difficulté du sudoku, en utilisant un algorithme de résolution;
* \param uint8_t** grille du sudoku cloner (libéré à la fin de la fonction.)
* \param size_t taille : taille du sudoku
* \param int level : niveau demandé par le jeu.
* \return int difficulte : retourne la difficulte de l'algorithme = {0: Non résovable/Plusieur solution, 1 : Facile, 2: Moyen, 3: Difficile, 4: Expert, 5 : level dépassé}
*/
int validiterEtDifficulter(uint8_t **grille, size_t taille, int level);

/**
 * @brief fonction qui permet de determiner la difficulté du sudoku en utilisant les heuristiques.
 * @param uint8_t** grille du sudoku.
 * @param size_t taille : taille du sudoku
 * @param int level : niveau demandé par le jeu.
 * @return int difficulte : retourne la difficulte de l'algorithme = {1 : Facile, 2: Moyen, 3: Difficile, 4: Expert, 5 : level dépassé}
 */
int difficulter(uint8_t **grille, size_t taille, int level);

/**
 * @brief fonction qui genere une liste 64 bits avec une en-tete pour mémoire. (premiere case a 0.)
 * @param size_t n : taille d'un bloc.
 * @param uint8_t** grille : grille du sudoku.
 * @param uint8_t ** map : map des bloc du sudoku.
 * @return Liste* : liste generer.
 */
Liste* listeGenerer(size_t n, uint8_t** grille,uint8_t ** map);
/**
 * @brief fonction qui genere une liste 32 bits pour la validiter.
 * @param size_t n : taille d'un bloc.
 * @param uint8_t** grille : grille du sudoku.
 * @param uint32_t *bbL : bitboard des lignes.
 * @param uint32_t *bbC : bitboard des colonnes.
 * @param uint32_t *bbB : bitboard des bloc.
 * @param uint8_t ** map : map des bloc du sudoku.
 * @return Liste32* : liste generer.
 */
Liste32* liste32Generer(size_t n, uint8_t** grille,uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t ** map);
/**
 * @brief fonction qui genere une liste 64 bits.
 * @param size_t n : taille d'un bloc.
 * @param uint8_t** grille : grille du sudoku.
 * @param uint32_t *bbL : bitboard des lignes.
 * @param uint32_t *bbC : bitboard des colonnes.
 * @param uint32_t *bbB : bitboard des bloc.
 * @param uint8_t ** map : map des bloc du sudoku.
 * @return Liste32* : liste generer.
 */
Liste * liste64Generer(size_t n,uint8_t **grille, uint64_t* bbL, uint64_t* bbC, uint64_t* bbB,uint8_t ** map);


#endif