#ifndef __DIFFICULTE_H__
#define __DIFFICULTE_H__

#include <stdint.h>
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
* \param uint8_t** grille du sudoku
* \param size_t taille : taille du sudoku
* \param int level : niveau demandé par le jeu.
* \return int difficulte : retourne la difficulte de l'algorithme = {0: Non résovable/Plusieur solution, 1 : Facile, 2: Moyen, 3: Difficile, 4: Expert, 5 : level dépassé}
*/
int validiter_et_difficulter(uint8_t **grille, size_t taille, int level);

#endif