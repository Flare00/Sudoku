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
/** @brief Liste de candidats pour les cases vides
  * @param uint8_t **grille : grille utilisée pour remplir le tableau de bits
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau permettant de savoir les indices de block pour le tableau de bit.
  * @return Liste* : le pointeur  sur la liste de candidat(s) solo
  */
Liste* rechercheCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);

#endif
