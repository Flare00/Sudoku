#ifndef __INTERFACEGTK_H__
#define __INTERFACEGTK_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

void transitionTEST();


/**
  * Widgets Globaux (Fenetre, Grilles, Constructeurs, Erreurs)
  */
GtkBuilder *constructeur;
GObject *fenetre;
GObject *grilleMenu;
GObject *grilleDifficulte;
GObject *grilleRegles;
GObject *grilleOptions;
GError *erreur;
GtkCssProvider *gtkCSS;

/**
  * Structure de données pour garder une trace des boutons du sudoku
  * et permettre l'assignement des signaux via constructeur XML.
  */
typedef struct boutonSudoku {
  // Menu
  GObject *boutonJouer;
  GObject *boutonResolution;
  GObject *boutonRegles;
  GObject *boutonOptions;
  GObject *boutonQuitter;
  //Difficulte
  GObject *boutonFacileDifficulte;
  GObject *boutonNormalDifficulte;
  GObject *boutonDifficileDifficulte;
  GObject *boutonExpertDifficulte;
  GObject *boutonRetourDifficulte;
  // Règles
  GObject *boutonRetourRegles;
  // Options
  GObject *switchResolution;
  GObject *switchSurlignerNombre;
  GObject *switchSurlignerZone;
  GObject *boutonRetourOptions;
} b_Sudoku;


/** @brief Transition du menu aux règles
  * @return void : affichage
  */
void transitionMenuRegles();


/** @brief Transition des règles au menu
  * @return void : affichage
  */
void transitionReglesMenu();


/** @brief Transition du menu aux options
  * @return void : affichage
  */
void transitionMenuOptions();


/** @brief Transition des options au menu
  * @return void : affichage
  */
void transitionOptionsMenu();


/** @brief Transition du menu à la difficulte
  * @return void : affichage
  */
void transitionMenuDifficulte();


/** @brief Transition de la difficulte au menu
  * @return void : affichage
  */
void transitionDifficulteMenu();


/** @brief Changement de Résolution de la fenetre
  * @param GtkComboBox *widget, gpointer user_data : widget appelant
  * @return void : redimension
  */
void changementResolution(GtkComboBox *widget, gpointer user_data);


/** @brief Creer l'interface "menu" GTK
  * @param b_Sudoku* bouton_Struct : structure contenant les traces des boutons du sudoku
  * @return void : construction
  */
void menuCreer(b_Sudoku *bouton_Struct);


/** @brief Creer l'interface "regles" GTK
  * @param b_Sudoku* bouton_Struct : structure contenant les traces des boutons du sudoku
  * @return void : construction
  */
void reglesCreer(b_Sudoku *bouton_Struct);


/** @brief Creer l'interface "options" GTK
  * @param b_Sudoku* bouton_Struct : structure contenant les traces des boutons du sudoku
  * @return void : construction
  */
void optionsCreer(b_Sudoku *bouton_Struct);

/** @brief Creer l'interface "difficulte" GTK
  * @param b_Sudoku* bouton_Struct : structure contenant les traces des boutons du sudoku
  * @return void : construction
  */
void difficulteCreer(b_Sudoku *bouton_Struct);



G_END_DECLS

#endif /* __INTERFACEGTK_H__ */
