#ifndef __SUDOKUGTK_H__
#define __SUDOKUGTK_H__

#include <gtk/gtk.h>
#include <math.h>

G_BEGIN_DECLS



void print_hello (GtkWidget *widget, gpointer data);


/**
 * @brief Vérification du contenu des cases du Sudoku.
 *
 * @param widget        Case du Sudoku appelante.
 * @param event         Événement déclenchant le signal.
 * @param tailleSudoku  Taille du Sudoku.
 * @return void
 */
void enter_callback(GtkEntry *widget, GdkEvent *event, gpointer tailleSudoku);


/**
 * @brief Création de l'interface Sudoku.
 *
 * @param taille        Taille du Sudoku.
 * @return void
 */
void sudokuCreer(int taille);



G_END_DECLS

#endif /* __SUDOKUGTK_H__ */
