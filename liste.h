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
  * @param size_t i, j : coordonnées d'une case de la grille
  * @param size_t *c : pointeur sur un tableau contenant les indices des bits à 1 dans l'entier candidats
  * @param int population : le nombre de bits à 1 présents dans candidats
  * @param uint64_t candidats : entier stockant les candidats de la case de la liste
  * @param struct Liste *suivante, *precedente : pointeur sur lélément suivant
    et préccédent sur une struct Liste
*/
typedef struct Liste{
    size_t i, j, *c;
    int population;
    uint64_t candidats;
    struct Liste *suivante, *precedente;
}Liste;

/**
  * @struct Liste32
  * @brief Liste32 de case vide de la grille
  *
  * Liste32 servant à générer un ordre de priorité sur les cases vide
    de la grille du sudoku à résoudre par rapport au nombre de
    candidats pour une case donnée
  *
  * @param size_t i, j : coordonnées d'une case de la grille
  * @param size_t *c : pointeur sur un tableau contenant les indices des bits à 1 dans l'entier candidats
  * @param int population : le nombre de bits à 1 présents dans candidats
  * @param uint32_t candidats : entier stockant les candidats de la case de la liste
  * @param struct Liste32 *suivante, *precedente : pointeur sur lélément suivant
    et préccédent sur une struct Liste32
*/
typedef struct Liste32{
    size_t i, j, *c;
    int population;
    uint32_t candidats;
    struct Liste32 *suivante, *precedente;
}Liste32;

/** @brief Ajoute un élément dans la liste en fonction de la population de manière croissante
  * @param Liste *dl : un pointeur sur une liste
  * @param uint64_t candidats : l'entiers représentant les candidats à insérer dans la liste.
  * @param  size_t i, j : les coordonnées de la case vide concernée
  */
Liste *listeInsertionOrdonnee(Liste *dl, uint64_t candidats, size_t i, size_t j);

/** @brief Ajoute un élément dans la liste en fonction de la population de manière croissante
  * @param Liste *dl : un pointeur sur une liste
  * @param uint64_t candidats : l'entiers représentant les candidats à insérer dans la liste.
  * @param  size_t i, j : les coordonnées de la case vide concernée
  */
Liste32 *listeInsertionOrdonnee32(Liste32 *dl, uint32_t candidats, size_t i, size_t j);

/** @brief Ajouter un élément en tête de liste
  * @param Liste *liste : pointeur sur la liste tête de la liste
  * @param uint64_t candidats : entier représentant les candidats pour une case de coord(i;j) dans une grille
  * @param size_t i, j : coordonnées de la case concernée
  * @return Liste* : la nouvelle tête de la liste
  */
Liste* listeAjouterEnTete(Liste *liste, uint64_t candidats, size_t i, size_t j);

/** @brief Ajouter un élément en tête de liste
  * @param Liste *liste : pointeur sur la liste tête de la liste
  * @param uint32_t candidats : entier représentant les candidats pour une case de coord(i;j) dans une grille
  * @param size_t i, j : coordonnées de la case concernée
  * @return Liste* : la nouvelle tête de la liste
  */
Liste32* listeAjouterEnTete32(Liste32 *liste, uint32_t candidats, size_t i, size_t j);

/** @brief Créer une liste pour les cases à un seul candidat
  * @param size_t n : le nombre de cases par ligne ou colonne de blocks
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  * @param uint8_t** map : tableau des indices de block de chaque case pour bbB
  * @return Liste* : tête de la liste
  */
Liste* listeCreerUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);

/** @brief Créer une liste pour les cases à un seul candidat
  * @param size_t n : le nombre de cases par ligne ou colonne de blocks
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block
  * @param uint8_t** grille : pointeur sur la grille
  * @param uint8_t** map : tableau des indices de block de chaque case pour bbB
  * @return Liste* : tête de la liste
  */
Liste32* listeCreerUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map);

/** @brief Renvoyer le nombre de listes suivantes du pointeur+1
  * @param Liste *l1 : un pointeur sur une liste
  * @return size_t : le nombre de listes à partir de l1*/
size_t listeNbElement(Liste *l1);

/** @brief Renvoyer le nombre de listes suivantes du pointeur+1
  * @param Liste32 *l1 : un pointeur sur une liste
  * @return size_t : le nombre de listes à partir de l1*/
size_t listeNbElement32(Liste32 *l1);

/** @brief Renvoyer le nombre total de candidats de la grille
  * @param Liste *l1 : un pointeur sur la liste à partir de laquelle compter
  * @return size_t : le nombre candidat compté à partir de l1*/
size_t listeNbCandidat(Liste *l1);

/** @brief Renvoyer le nombre total de candidats de la grille
  * @param Liste32 *l1 : un pointeur sur la liste à partir de laquelle compter
  * @return size_t : le nombre candidat compté à partir de l1*/
size_t listeNbCandida32(Liste32 *l1);

/** @brief Supprimer la liste à partir de dl
  * @param Liste *dl : liste à partir de laquelle réaliser la suppression
  */
void listeDetruire(Liste *dl);

/** @brief Supprimer la liste à partir de dl
  * @param Liste32 *dl : liste à partir de laquelle réaliser la suppression
  */
void listeDetruire32(Liste32 *dl);

/** @brief Supprimer la tête d'une liste
  * @param Liste *dl : un pointeur sur la tête de la liste
  */
void listeDetruireTete(Liste **dl);

/** @brief Supprimer la tête d'une liste
  * @param Liste32 *dl : un pointeur sur la tête de la liste
  */
void listeDetruireTete32(Liste32 **dl);

/** @brief Créer une liste de candidats de chaque case par ordre de population croissant
  * @param uint8_t **grille : tableau à deux dimensions dont ont souhaite obtenir les cases vides
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint64_t* bbL : tableau de bits ligne
  * @param uint64_t* bbC : tableau de bits colonne
  * @param uint64_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau des indices de chaque block
  * @return Liste* : un pointeur sur le début de la liste de candidats
  */
Liste* listeRechercherCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map);

/** @brief Créer une liste de candidats de chaque case par ordre de population croissant
  * @param uint8_t **grille : tableau à deux dimensions dont ont souhaite obtenir les cases vides
  * @param size_t n : nombre de lignes ou colonnes de blocks
  * @param uint32_t* bbL : tableau de bits ligne
  * @param uint32_t* bbC : tableau de bits colonne
  * @param uint32_t* bbB : tableau de bits block
  * @param uint8_t** map : tableau des indices de chaque block
  * @return Liste32* : un pointeur sur le début de la liste de candidats
  */
Liste32* listeRechercherCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map);

/** @brief Afficher le contenu des éléments de la liste à partir de l
  * @param Liste3 *dl : pointeur sur le début de la liste à afficher
  */
void listeAfficher(Liste* l);

/** @brief Afficher le contenu des éléments de la liste à partir de l
  * @param Liste32 *dl : pointeur sur le début de la liste à afficher
  */
void listeAfficher32(Liste32* l);

#endif
