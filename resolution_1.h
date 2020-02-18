#ifndef RESOLUTION_1_H
#define RESOLUTION_1_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char characterMap[64]  =  "123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ>?@";

/** @brief Creer une grille à partir d'une chaine de caractères
  * @param char* chaine : chaine de caractères à repartir dans la grille
  * @param size_t hauteur : nombre de case par ligne ou colonne de la grille
  * @return int8_t** : un tableau à 2 dimensions */
int8_t **creer_grille(char *chaine, size_t hauteur);

/** @brief Destruction de la grille
  * @param int8_t **grille : grille à détruire
  * @param size_t hauteur : nombre de ligne à libérer*/
void detruire_grille(int8_t **grille, size_t hauteur);

void afficherGrille(size_t hauteur, int8_t **grille);

#endif