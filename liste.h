#ifndef LISTE_H
#define LISTE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Liste{
    size_t i,j;
    int population;
    size_t *c;
    uint64_t candidats;
    struct Liste *suivante, *precedente;
}Liste;

/** @brief Ajoute un élément dans la liste avec un classement croissant des populations
  * @param Liste *dl :un pointeur sur une liste en entrée
  * @param uint64_t candidats : le candidat de l'élément à insérer
  * @param  size_t i, size_t j : la position dans la grille
  */
Liste *insertionListe(Liste *dl, uint64_t candidats, size_t i, size_t j);

/** @brief Renvoie le nombre d'éléments d'une liste
  * @param Liste *l1 : un pointeur sur une liste
  * @return size_t : le nombre d'éléments de l1*/
size_t nbElementListe(Liste *l1);

/** @brief Renvoie le nombre d'éléments d'une liste
  * @param Liste *l1 : un pointeur sur une liste
  * @return size_t : le nombre d'éléments de l1*/
size_t nbCandidatListe(Liste *l1);

/** @brief Supprime la liste entière
  * @param Liste *dl :un pointeur sur une liste
  */
void detruireListe(Liste *dl);

void afficherListe(Liste* liste);

#endif
