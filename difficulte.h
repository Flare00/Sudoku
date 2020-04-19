#ifndef __DIFFICULTE_H__
#define __DIFFICULTE_H__

#include <stdint.h>
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

int difficulter(uint8_t **grille, size_t taille, int level);

Liste* listeGenerer(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille);

#endif