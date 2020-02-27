#ifndef __GENENERATION_H__
#define __GENENERATION_H__

#include <stdint.h>
#include <stdlib.h>

struct pos_case 
{
    size_t colonne;
    size_t ligne;
};

/**
* \brief Génère chaine correspondant à une grille de sudoku Valide et de difficulté donnée.
* \param int taille : taille de la grille de sudoku
* \param int level : le niveau de difficulté nécéssaire pour la grille
* \return unisgned int * : chaine correspondant à la grille de sudoku.
*/
unsigned int *generer_chaine_sudoku(size_t taille, int level);

/**
* \brief Génère une grille de sudoku valide et de difficulté donnée.
* \param int taille : taille de la grille de sudoku
* \param int level : le niveau de difficulté nécéssaire pour la grille
* \return uint8_t ** : la grille de sudoku.
*/
uint8_t **generer_grille_sudoku(size_t taille, int level);

/**
 * \brief retire une case, parmi les cases non vide, de la grille de façon aléatoire.
 * \param uint8_t grille grille : grille du sudoku 
 * \return nombre de cases restante.
 */ 
size_t retirer_case_random(uint8_t ** grille, size_t taille);

/**
 * \brief genere une grille de sudoku complete.
 * \param size_t taille : taille de la grille.
 * \return grille de sudoku complete.
 */
uint8_t generer_grille_complete(size_t taille);

#endif