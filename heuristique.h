#ifndef __HEURISTIQUE_H__
#define __HEURISTIQUE_H__

#include <stdint.h>
#include "liste.h"
/**
 * @brief execute toutes les heuristique de niveau Facile.
 * @param uint8_t** grille : pointeur sur la grille
 * @param size_t n : taille d'un bloc
 * @param Liste * liste : Liste des candidats par cases.
 * @param uint8_t** map : map du sudoku, element donnant le bloc a laquel appartient la case donnée.
 * @return nombre de cases restantes à remplir.
 */
size_t heuristiqueFacile(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map);
/**
 * @brief execute toutes les heuristique de niveau Moyen, plus les heuristique de niveau Facile.
 * @param uint8_t** grille : pointeur sur la grille
 * @param size_t n : taille d'un bloc
 * @param Liste * liste : Liste des candidats par cases.
 * @param uint8_t** map : map du sudoku, element donnant le bloc a laquel appartient la case donnée.
 * @return nombre de cases restantes à remplir.
 */
size_t heuristiqueMoyenne(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map);

/**
 * @brief execute toutes les heuristique de niveau Difficile, plus les heuristiques de niveau Moyen et Facile.
 * @param uint8_t** grille : pointeur sur la grille
 * @param size_t n : taille d'un bloc
 * @param Liste * liste : Liste des candidats par cases.
 * @param uint8_t** map : map du sudoku, element donnant le bloc a laquel appartient la case donnée.
 * @return nombre de cases restantes à remplir.
 */
size_t heuristiqueDifficile(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map);

//Niveau Facile
//void heuristiqueSingleton(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map);
/**
 * @brief fonction heuristique permetant d'effectuer la technique Singleton Visible
 * 
 * @param uint8_t** grille : pointeur sur la grille
 * @param size_t n : taille d'un bloc
 * @param Liste * liste : Liste des candidats par cases.
 * @param uint8_t** map : map du sudoku, element donnant le bloc a laquel appartient la case donnée.
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueSingletonVisible(uint8_t **grille, size_t n, Liste *liste, uint8_t** map);
/**
 * @brief fonction heuristique permetant d'effectuer la technique Singleton Cacher
 * 
 * @param uint8_t** grille : pointeur sur la grille
 * @param size_t n : taille d'un bloc
 * @param Liste * liste : Liste des candidats par cases.
 * @param uint8_t** map : map du sudoku, element donnant le bloc a laquel appartient la case donnée.
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueSingletonCacher(uint8_t **grille, size_t n, Liste *liste, uint8_t** map);
/**
 * @brief fonction heuristique permetant d'effectuer les techniques Singletons en simultanée
 * 
 * @param uint8_t** grille : pointeur sur la grille
 * @param size_t n : taille d'un bloc
 * @param Liste * liste : Liste des candidats par cases.
 * @param uint8_t** map : map du sudoku, element donnant le bloc a laquel appartient la case donnée.
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueSingleton(uint8_t **grille, size_t n, Liste *liste, uint8_t** map);

//Niveau Moyen
/**
 * @brief fonction heuristique permettant d'effectuer la technique de Jumeau, Triple, et N Visible. 
 * 
 * Si dans une région R de largeur N, un candidats C est présent entre 2 et N fois, et strictement aligné sur une ligne ou une colonne, 
 * alors pour le reste de la ligne/colonne, C ne peut pas être présent, et nous pouvons  donc supprimé ses occurrences.
 * https://www.mots-croises.ch/Manuels/Sudoku/jumeaux.htm
 *
 * @param size_t n : taille d'un bloc
 * @param Liste * liste : Liste des candidats par cases.
 * @param uint8_t** map : map du sudoku, element donnant le bloc a laquel appartient la case donnée.
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueJumeauANVisible( size_t n, Liste *liste, uint8_t ** map);

//Niveau Difficile
/**
 * @brief fonction heuristique permettant d'effectuer la technique de Groupes Isolés
 * 
 * Si pour une même ligne/colonne, N groupe de M candidats C (strictement identique ou identique avec candidats manquant) (M compris entre 2 et N),
 * dont 1 contient les N candidats, sur N cases de la ligne/colonne, alors ces candidats ne peuvent pas être présent sur les autres cases de la ligne/colonne.
 * https://www.mots-croises.ch/Manuels/Sudoku/groupes_isoles.htm
 * @param size_t n : taille d'un bloc
 * @param Liste * liste : Liste des candidats par cases.
 * @return uint8_t : retourne 0 si aucune modification n'as été faite, 1 sinon.
 */
uint8_t heuristiqueGroupesIsoler(size_t n, Liste *liste);

#endif
