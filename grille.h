#ifndef GRILLE_H
#define GRILLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define block(a, b,n)    (((a/n)*n)+b/n)

#define bool uint8_t
#define true 1
#define false 0

/** @brief Creer une grille à partir d'un tableau d'entiers
  * @param unsigned int* chaine : tableau d'entiers à repartir dans la grille
  * @param size_t taille : nombre de case par ligne ou colonne de la grille
  * @return int8_t** : un tableau de caractères non signés à 2 dimensions */
uint8_t **grilleCreer(uint8_t *chaine, size_t taille);

/** @brief Détruire la grille
  * @param int8_t **grille : grille à détruire
  * @param size_t taille : nombre de sous-tableau à libérer*/
void grilleDetruire(uint8_t **grille, size_t taille);

/** @brief Creer une map qui à partir des coordonnées des lignes et colonnes renvoit l'indice du block
  * @param size_t n : taille d'un block
  * @return uint8_t** : un tableau qui représente la map */
uint8_t** mapCreer(size_t n);

/** @brief Détruire le tableau à 2 dimensions
  * @param size_t taille : même taille que celle de la grille
  * @param uint8_t **map : un tableau qui représente la map */
void mapDetruire(uint8_t **map, size_t taille);

void afficherGrille(size_t taille, size_t n, uint8_t **grille);

#endif
