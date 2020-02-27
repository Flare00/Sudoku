#ifndef __COM_IHM_METIER_H__
#define __COM_IHM_METIER_H__
#include <stdint.h>

/**
 * Metier -> IHM
 * \brief Demande une mise a jour de l'affichage avec une grille de sudoku particuliere.
 * \param int8_t grille : grille a afficher.
 */
void update_affichage(int8_t ** grille);



/**
 * IHM -> Metier
 * \brief demande au métier de généré une grille de sudoku.
 * \param int8_t grille : grille a résoudre.
 * \return int8_t : retourne la grille résolu
 */ 
int8_t ** demande_generation(int level);

/**
 * IHM -> Metier
 * \brief demande au métier de résoudre la grille.
 * \param int8_t grille : grille a résoudre.
 * \return int8_t : retourne la grille résolu
 */ 
int8_t ** demande_resolution (int8_t **grille);


/**
 * IHM -> Metier
 * \brief demande au métier de résoudre la grille étape par étape.
 * \param int8_t grille : grille a résoudre.
 */ 
//void demande_resolution_step_by_step(int8_t grille);

/**
 * IHM -> Metier
 * \brief Envoie l'input de l'utilisateur au métier
 */
//void input_utilisateur(char input, size_t pos_ligne, size_t pos_colonne);
#endif