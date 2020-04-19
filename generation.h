#ifndef __GENENERATION_H__
#define __GENENERATION_H__

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "difficulte.h"
/**
* \brief Génère une grille de sudoku valide et de difficulté donnée.
* \param taille size_t : taille de la grille de sudoku
* \param niveauDemander int : le niveau de difficulté nécéssaire pour la grille
* \return uint8_t ** : la grille de sudoku.
*/
uint8_t **genererGrilleSudokuValide(size_t taille, size_t niveauDemander);

/**
 * \brief retire une case, parmi les cases non vide, de la grille de façon aléatoire.
 * \param uint8_t** grille : grille du sudoku.
 * \return nombre de cases restante.
 */
//size_t retirerCaseRandomAvecCaseRestante(uint8_t ** grille, size_t taille);

/**
 * \brief retire une case, parmi les cases non vide, de la grille de façon aléatoire.
 * \param uint8_t** grille : grille du sudoku.
 * \param size_t taille : taille de la grille.
 */
void retirerCaseRandom(uint8_t ** grille, size_t taille);

/**
 * \brief retire une case, parmi les cases non vide, de la grille de façon aléatoire et son symétrique selon le centre du sudoku.
 * \param uint8_t** grille : grille du sudoku.
 * \param size_t taille : taille de la grille.
 * \return size_t : nombre de case retirer (1 ou 2);
 */
size_t retirerCaseSymetrie(uint8_t ** grille, size_t taille);
/**
 * \brief genere une grille de sudoku complete.
 * \param size_t taille : taille de la grille.
 * \return grille de sudoku complete.
 */
uint8_t **genererGrilleComplete(size_t taille);

/**
 * \brief permute les lignes d'une grille de sudoku.
 * \param uint8_t** grille : grille du sudoku.
 * \param size_t taille : taille de la grille.
 */
void permuterLignes(uint8_t ** grille, size_t taille);

/**
 * \brief permute les colonnes de la grille de sudoku donnée.
 * \param uint8_t** grille : grille du sudoku.
 * \param size_t taille : taille de la grille.
 */
void permuterColonnes(uint8_t ** grille, size_t taille);

/**
 * \brief echange deux ligne de la grille de sudoku donnée.
 * \param uint8_t** grille : grille du sudoku.
 * \param size_t taille : taille de la grille.
 * \param size_t ligne1 : ligne à echanger.
 * \param size_t ligne2 : ligne à echanger.
 */
void echangerLignes(uint8_t ** grille, size_t taille, size_t ligne1, size_t ligne2);

/**
 * \brief echange deux colonnes de la grille de sudoku donnée.
 * \param uint8_t** grille : grille du sudoku.
 * \param size_t taille : taille de la grille.
 * \param size_t colonne1 : colonne à echanger.
 * \param size_t colonne2 : colonne à echanger.
 */
void echangerColonnes(uint8_t ** grille, size_t taille, size_t colonne1, size_t colonne2);

/**
 * \brief renvoie un clone de la grille de taille taille.
 * \param uint8_t** grille : grille du sudoku.
 * \param size_t taille : taille de la grille.
 * \return uint8_t** : clone de la grille.
 */
uint8_t** grilleCloner(uint8_t ** grille, size_t taille);

#endif
