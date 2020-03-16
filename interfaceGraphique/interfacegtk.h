#ifndef __INTERFACEGTK_H__
#define __INTERFACEGTK_H__

#include <gtk/gtk.h>


G_BEGIN_DECLS


// Widgets GLOBAUX
GtkBuilder *constructeur;
GObject *fenetre;
GObject *grilleMenu;
GObject *grilleRegles;
GError *erreur;

/**
  * structure de données pour garder une trace des boutons du sudoku
  */
typedef struct boutonSudoku {
  // Menu
  GObject *boutonJouer;
  GObject *boutonRegles;
  GObject *boutonOptions;
  GObject *boutonQuitter;
  // Règles
  GObject *boutonRetourRegles;
} b_Sudoku;


void print_hello (GtkWidget *widget, gpointer data);


/** @brief Transition du menu aux règles
  * @return void : affichage
  */
void transitionMenuRegles();


/** @brief Transition des règles au menu
  * @return void : affichage
  */
void transitionReglesMenu();


/** @brief Creer l'interface menu GTK
  * @param b_Sudoku* bouton_Struct : structure contenant les traces des boutons du sudoku
  * @return void : construction
  */
void menuCreer(b_Sudoku *bouton_Struct);


/** @brief Creer l'interface menu GTK
  * @param b_Sudoku* bouton_Struct : structure contenant les traces des boutons du sudoku
  * @return void : construction
  */
void reglesCreer(b_Sudoku *bouton_Struct);


G_END_DECLS

#endif /* __INTERFACEGTK_H__ */
