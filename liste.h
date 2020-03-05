#ifndef LISTE_H
#define LISTE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Liste{ // __builtin_popcount renvoie un int
    size_t i,j; // i et j ou seulement i si on travaille sur un tableau unidimensionnel
    int population;
    uint64_t candidats;
    struct Liste *next, *back;
}Liste;

/** @brief Enlève le premier élément de la liste
  * @param Liste *dl : un pointeur sur une liste en entrée
  * @return uint64_t le candidat du premier élément*/
uint64_t depilerListe(Liste *dl);

/** @brief Ajoute un élément dans la liste avec un classement croissant des populations
  * @param Liste *dl :un pointeur sur une liste en entrée
  * @param uint64_t candidats : le candidat de l'élément à insérer
  * @param  size_t i, size_t j : la position dans la grille
  */
Liste *insertionListe(Liste *dl, uint64_t candidats, size_t i, size_t j);

void detruireListe(Liste *dl);

/** @brief Affiche la liste
  * @param Liste *dl : une liste en entrée
  */
void afficherListe(Liste* liste);

#endif
