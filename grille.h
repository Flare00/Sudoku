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
  * @param uint8_t* chaine : tableau d'entiers à repartir dans la grille
  * @param size_t taille : nombre de case par ligne, colonne ou block de la grille
  * @return int8_t** : un tableau à 2 dimensions représentant la grille*/
uint8_t** grilleCreer(uint8_t *chaine, size_t taille);

/** @brief Creer une map qui à partir des coordonnées des lignes et colonnes renvoit l'indice du block
  * @param size_t n : nombre de case par ligne ou colonne de blocks
  * @return uint8_t** : tableau permettant de savoir l'indice du block pour une case à partir des indices ligne et colonne */
uint8_t** mapCreer(size_t n);

/** @brief Détruire le tableau à 2 dimensions
  * @param size_t taille : nombre de sous tableaux
  * @param uint8_t **tableau2D : le tableau à détruire*/
void detruire2D(uint8_t **tableau2D, size_t taille);

/** @brief Afficher le tableau à 2 dimensions
  * @param size_t n : nombre de case par ligne ou colonne de blocks
  * @param uint8_t** grille : le tableau à afficher*/
void afficher2D(size_t n, uint8_t **grille);

#endif
