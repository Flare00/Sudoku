#ifndef LISTE_H
#define LISTE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/**
  * @struct Liste
  * @brief Liste de case vide de la grille 
  * 
  * Liste servant à générer un ordre de priorité sur les cases vide
    de la grille du sudoku à résoudre par rapport au nombre de
    candidats pour une case donnée
  *
  * @param size_t i, j : Coordonnée d'une case de la grille
  * @param size_t *c : pointeur sur un tableau contenant les indices 
    des bits à 1 de l'entier candidats
  * @param int population : le nombre de bits à 1 présents dans candidats
  * @param uint64_t candidats : entier sur 64 bits contenant les candidats 
    de la case tel que pour la position n < à la taille de la grille (max 64)
    au bit à 1, on la la valeur n+1 pour la case
  * @param struct Liste *suivante, *precedente : pointeur sur lélément suivant 
    et précédent du pointeur actuel sur une struct Liste
*/
typedef struct Liste{
    size_t i, j, *c;
    int population;
    uint64_t candidats;
    struct Liste *suivante, *precedente;
}Liste;

typedef struct Liste32{
    size_t i, j, *c;
    int population;
    uint32_t candidats;
    struct Liste32 *suivante, *precedente;
}Liste32;

/** @brief Ajoute un élément dans la liste avec un classement croissant des populations
  * @param Liste *dl :un pointeur sur une liste en entrée
  * @param uint64_t candidats : le candidat de l'élément à insérer
  * @param  size_t i, size_t j : la position dans la grille
  */
Liste *listeInsertionOrdonnee(Liste *dl, uint64_t candidats, size_t i, size_t j);
Liste32 *listeInsertionOrdonnee32(Liste32 *dl, uint32_t candidats, size_t i, size_t j);

/** @brief Renvoyer le nombre d'éléments d'une liste
  * @param Liste *l1 : un pointeur sur une liste
  * @return size_t : le nombre d'éléments de l1*/
size_t listeNbElement(Liste *l1);
size_t listeNbElement32(Liste32 *l1);

/** @brief Renvoyer le nombre total de candidats de la grille
  * @param Liste *l1 : un pointeur sur une liste
  * @return size_t : le nombre candidat de tout l1*/
size_t listeNbCandidat(Liste *l1);
size_t listeNbCandida32(Liste32 *l1);

/** @brief Supprime la liste entière
  * @param Liste *dl :un pointeur sur une liste
  */
void listeDetruire(Liste *dl);
void listeDetruire32(Liste32 *dl);

/** @brief Liste de candidats pour les cases vides
  * @param uint8_t **grille : grille utilisée pour remplir le tableau de bits
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau permettant de savoir les indices de block pour le tableau de bit.
  * @return Liste* : le pointeur  sur la liste de candidat(s) solo
  */
Liste* rechercherCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);
Liste32* rechercherCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map);

void afficherListe(Liste* liste);

#endif
