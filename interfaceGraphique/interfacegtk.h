#ifndef __INTERFACEGTK_H__
#define __INTERFACEGTK_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS



/**
  * Widgets Globaux (Fenetre, Grilles, Constructeurs, Erreurs)
  */
GtkBuilder *constructeur;
GObject *fenetre;
GObject *grilleMenu;
GObject *grilleDifficulte;
GObject *grilleRegles;
GObject *grilleOptions;

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


void transitionTEST();


/** @brief Transition du menu à une grille
  * @param GtkWidget *widget, gpointer user_data : widget appelant, pointeur envoyé
  * @return void : affichage
  */
void transitionMenu(GtkWidget *widget, gpointer data);


/** @brief Transition d'une grille au menu
  * @param GtkWidget *widget, gpointer user_data : widget appelant, pointeur envoyé
  * @return void : affichage
  */
void transitionGrille(GtkWidget *widget, gpointer data);


/** @brief Changement de Résolution de la fenetre
  * @param GtkComboBox *widget, gpointer user_data : widget appelant, pointeur envoyé
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
