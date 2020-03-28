#ifndef __SUDOKUGTK_H__
#define __SUDOKUGTK_H__

#include <gtk/gtk.h>
#include <math.h>

G_BEGIN_DECLS



// Test
void print_hello (GtkWidget *widget, gpointer data);




/**
 * Création du tableau maximum du Sudoku.
 */
GtkWidget *caseSudoku[64][64];


/**
 * @brief Création des tableaux des coordonnées de chaque case du Sudoku.
 *
 * @param t             Taille du Sudoku.
 * @param x             Ligne de la case du Sudoku appelante.
 * @param y             Colonne de la case du Sudoku appelante.
 * @return int*         Tableau contenant les coordonnées (x,y) ainsi que la taille.
 */
int* envoiCoords(int t, int x, int y);


/**
 * @brief Vérification de la ligne qui contient la case du Sudoku appelante.
 *
 * @param t             Taille du Sudoku.
 * @param l             Ligne de la case du Sudoku appelante.
 * @param c             Colonne de la case du Sudoku appelante.
 * @param val           Valeur de la case du Sudoku appelante.
 * @return char         Booléen simplifié, renvoie VRAI si la val existe déjà dans la ligne séléctionnée.
 */
char verifLigne(int t, int l, int c, const char *val);


/**
 * @brief Vérification de la colonne qui contient la case du Sudoku appelante.
 *
 * @param t             Taille du Sudoku.
 * @param l             Ligne de la case du Sudoku appelante.
 * @param c             Colonne de la case du Sudoku appelante.
 * @param val           Valeur de la case du Sudoku appelante.
 * @return char         Booléen simplifié, renvoie VRAI si la val existe déjà dans la colonne séléctionnée.
 */
char verifColonne(int t, int l, int c, const char *val);


/**
 * @brief Vérification du carré qui contient la case du Sudoku appelante.
 *
 * @param t             Taille du Sudoku.
 * @param l             Ligne de la case du Sudoku appelante.
 * @param c             Colonne de la case du Sudoku appelante.
 * @param val           Valeur de la case du Sudoku appelante.
 * @return char         Booléen simplifié, renvoie VRAI si la val existe déjà dans le carré séléctionnée.
 */
char verifCarre(int t, int l, int c, const char *val);


/**
 * @brief Vérification du contenu de la case du Sudoku appelante.
 *
 * @param t             Taille du Sudoku.
 * @param val           Valeur de la case du Sudoku appelante.
 * @return char         Booléen simplifié, renvoie VRAI si la val est comprise dans la liste caracDispo.
 */
char verifChar(int t, const char *val);


/**
 * @brief Fonction contenant les fonctions de vérification du contenu des cases du Sudoku.
 *
 * @param widget        Case du Sudoku appelante.
 * @param evenement     Événement déclenchant le signal.
 * @param donnee        Tableau de coordonnées (x,y) avec la taille du Sudoku.
 * @return void         En fonction des vérifications, le contenu de la case peut être supprimé.
 */
void sortieCase(GtkEntry *widget, GdkEvent *evenement, gpointer donnee);


/**
 * @brief Fonction contenant les Surlignements des cases du Sudoku.
 *
 * @param widget        Case du Sudoku appelante.
 * @param evenement     Événement déclenchant le signal.
 * @param donnee        Tableau de coordonnées (x,y) avec la taille du Sudoku.
 * @return void         Application du CSS en fonction de la ligne - colonne - carré de la case appelante.
 */
void entreeCase(GtkEntry *widget, GdkEvent *evenement, gpointer donnee);


/**
 * @brief Création de l'interface Sudoku.
 *
 * @param taille        Taille du Sudoku.
 * @return void         Création du Sudoku
 */
void sudokuCreer(int taille);



G_END_DECLS

#endif /* __SUDOKUGTK_H__ */
