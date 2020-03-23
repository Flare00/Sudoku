#ifndef __SUDOKUGTK_H__
#define __SUDOKUGTK_H__

#include <gtk/gtk.h>
#include <math.h>

G_BEGIN_DECLS



void print_hello (GtkWidget *widget, gpointer data);


/** @brief Vérification du contenu de l'entrée
  * @param GtkWidget *widget, GtkWidget *entry : widget appelant, contenue de l'entrée
  * @return static void : affichage
  */
void enter_callback(GtkEntry *widget, GdkEvent *event, gpointer data);


/** @brief Creer l'interface "Sudoku" GTK
  * @param int taille : Taille du sudoku
  * @return void : affichage
  */
void sudokuCreer(int taille);


G_END_DECLS

#endif /* __SUDOKUGTK_H__ */
