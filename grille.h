#ifndef GRILLE_H
#define GRILLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/** @brief Creer une grille à partir d'un tableau d'entiers
  * @param int* chaine : tableau d'entiers à repartir dans la grille
  * @param size_t taille : nombre de case par ligne ou colonne de la grille
  * @return int8_t** : un tableau de caractères non signés à 2 dimensions */
uint8_t **creerGrille(int *chaine, size_t taille);

/** @brief Destruction de la grille
  * @param int8_t **grille : grille à détruire
  * @param size_t taille : nombre de sous-tableau à libérer*/
void detruireGrille(uint8_t **grille, size_t taille);

void afficherGrille(size_t taille, size_t n, uint8_t **grille);

#endif
