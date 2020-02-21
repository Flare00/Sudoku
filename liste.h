#ifndef LISTE_H
#define LISTE_H
#include "resolution.h"

typedef struct Liste{ // __builtin_popcount renvoie un int
    size_t i,j; // i et j ou seulement i si on travaille sur un tableau unidimensionnel
    int population;
    uint64_t candidats;
    struct Liste *next;
}Liste;

/** @brief Enlève le premier élément de la liste
  * @param Liste **sl : un pointeur sur une liste en entrée
  * @return uint64_t le candidat du premier élément*/
uint64_t Pop(Liste **sl);

/** @brief Enlève le premier élément de la liste
  * @param Liste **sl :un pointeur sur une liste en entrée
  * @param uint64_t candidats : le candidat de l'élément à insérer
  * @param  size_t i, size_t j : la position dans la grille
  */
void Insert(Liste **sl, uint64_t candidats, size_t i, size_t j);

/** @brief Affiche la liste
  * @param Liste *sl : une liste en entrée
  */
void afficherListe(Liste* liste);

#endif
