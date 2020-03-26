#ifndef __INTERFACEGTK_H__
#define __INTERFACEGTK_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS



/**
  * Widgets Globaux (Fenetre, Grilles).
  */
GObject *fenetre;
GObject *grilleMenu;
GObject *grilleDifficulte;
GObject *grilleRegles;
GObject *grilleOptions;


// ---- !!! ---- A OPTIMISER  ---- !!! ---- //
/**
  * Structure de données permettant de garder une trace des boutons du sudoku
  * et ainsi permettre l'assignement des signaux via constructeur XML.
  */
typedef struct boutonSudoku {
  // Constructeur
  GtkBuilder *constructeur;
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


/**
 * @brief Transitions entre les différentes interfaces possibles.
 *
 * @param widget        Bouton appelant.
 * @param grille        Grille à afficher.
 * @return void
 */
void transitionInterface(GtkWidget *widget, gpointer grille);


/**
 * @brief Changement de résolution de la fenêtre principale.
 *
 * @param widget        Liste appelante.
 * @return void
 */
void changementResolution(GtkComboBox *widget);


/** @brief Creer l'interface "menu" GTK
  * @param b_Sudoku* bouton_Struct : structure contenant les traces des boutons du sudoku
  * @return void : construction
  */
// ---- !!! ---- A OPTIMISER  ---- !!! ---- //
void menuCreer(b_Sudoku *bouton_Struct);
void reglesCreer(b_Sudoku *bouton_Struct);
void optionsCreer(b_Sudoku *bouton_Struct);
void difficulteCreer(b_Sudoku *bouton_Struct);



G_END_DECLS

#endif /* __INTERFACEGTK_H__ */
