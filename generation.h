#ifndef __GENENERATION_H__
#define __GENENERATION_H__
#include <stdint.h>

/**
* \brief Génère chaine correspondant à une grille de sudoku Valide et de difficulté donnée.
* \param int level : le niveau de difficulté nécéssaire pour la grille
* \return unisgned int * : chaine correspondant à la grille de sudoku.
*/
unsigned int *generer_chaine_sudoku(int level);

/**
* \brief Génère une grille de sudoku valide et de difficulté donnée.
* \param int level : le niveau de difficulté nécéssaire pour la grille
* \return uint8_t ** : la grille de sudoku.
*/
uint8_t **generer_grille_sudoku(int level);

#endif