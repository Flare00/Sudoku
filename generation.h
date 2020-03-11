#ifndef __GENENERATION_H__
#define __GENENERATION_H__

#include <stdint.h>
#include <stdlib.h>

struct posCase{
    size_t ligne;
    size_t colonne;
}

/**
* \brief Génère chaine correspondant à une grille de sudoku Valide et de difficulté donnée.
* \param taille : taille de la grille de sudoku
* \param level : le niveau de difficulté nécéssaire pour la grille
* \return unisgned int * : chaine correspondant à la grille de sudoku.
*/
uint8_t * genererChaineSudoku(size_t taille, int level);

/**
* \brief Génère une grille de sudoku valide et de difficulté donnée.
* \param taille size_t : taille de la grille de sudoku
* \param level int : le niveau de difficulté nécéssaire pour la grille
* \return uint8_t ** : la grille de sudoku.
*/
uint8_t **genererGrilleSudoku(size_t taille, int level);

/**
 * \brief retire une case, parmi les cases non vide, de la grille de façon aléatoire.
 * \param grille : grille du sudoku 
 * \return nombre de cases restante.
 */ 
size_t retirerCaseRandomAvecCaseRestante(uint8_t ** grille, size_t taille);

/**
 * \brief retire une case, parmi les cases non vide, de la grille de façon aléatoire.
 * \param grille : grille du sudoku 
 * \return grille de sudoku.
 */ 
uint8_t ** retirerCaseRandom(uint8_t ** grille, size_t taille);

/**
 * \brief genere une grille de sudoku complete.
 * \param taille : taille de la grille.
 * \return grille de sudoku complete.
 */
uint8_t ** grilleComplete(size_t taille);

/**
 * \brief permute deux lignes de la grille de sudoku donnée.
 * \param grille : grille du sudoku.
 * \param taille : taille de la grille.
 * \param ligne1 : ligne à permuter.
 * \param ligne2 : ligne à permuter.
 * \return grille de sudoku permuté.
 */
uint8_t ** permutationLignes(uint8_t ** grille, size_t taille, size_t ligne1, size_t ligne2);

/**
 * \brief permute deux lignes de la grille de sudoku donnée.
 * \param grille : grille du sudoku.
 * \param taille : taille de la grille.
 * \param colone1 : colone à permuter.
 * \param colone2 : colone à permuter.
 * \return grille de sudoku permuté.
 */
uint8_t ** permutationColones(uint8_t ** grille, size_t taille, size_t colone1, size_t colone2);

/**
 * \brief permute deux lignes de la grille de sudoku donnée.
 * \param grille : grille du sudoku.
 * \param taille : taille de la grille.
 * \return grille de sudoku permuté.
 */
uint8_t ** rotation(uint8_t ** grille, size_t taille);


#endif