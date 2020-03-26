#ifndef __INTERFACEGTK_H__
#define __INTERFACEGTK_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS



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


/**
 * @brief Traduction du widget Scale en Taille sudoku n*n.
 *
 * @param widget        Scale appelant.
 * @param etiquette     Etiquette permettant l'affichage de la Traduction.
 * @return void         Affichage
 */
void scaleTrad(GtkRange *widget, gpointer etiquette);


/**
 * @brief Permet une configuration avant l'appel de la fonction Sudoku.
 *
 * @param widget        Bouton appelant (Valider).
 * @param range         Scale permettant de savoir quel valeur utiliser.
 * @return void         Affichage
 */
void appelSudoku(GtkRange *widget, gpointer range);



///////////////////////////////////////////////////////////////////////////////////////////
// ---- !!! ---- TOUT CE QUI EST EN DESSOUS EST A OPTIMISER IMPERATIVEMENT ---- !!! ---- //
///////////////////////////////////////////////////////////////////////////////////////////

/**
  * Widgets Globaux (Fenetre, Grilles).
  */
GObject *fenetre;
GObject *grilleMenu;
GObject *grilleDifficulte;
GObject *grilleRegles;
GObject *grilleOptions;
GObject *grilleResoudre;


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
  // Résoudre
  GObject *etiquetteTitreResoudre;
  GObject *boutonRetourResoudre;
  GObject *boutonValiderResoudre;
  GObject *scaleSudokuResoudre;
  GObject *etiquetteTraductionResoudre;
} b_Sudoku;


/** @brief Creer l'interface "menu" GTK
  * @param b_Sudoku* bouton_Struct : structure contenant les traces des boutons du sudoku
  * @return void : construction
  */
void menuCreer(b_Sudoku *bouton_Struct);
void reglesCreer(b_Sudoku *bouton_Struct);
void optionsCreer(b_Sudoku *bouton_Struct);
void difficulteCreer(b_Sudoku *bouton_Struct);
void resoudreCreer(b_Sudoku *bouton_Struct);

void changementSurligner(GObject *switcher, GParamSpec *pspec, gpointer user_data);



G_END_DECLS

#endif /* __INTERFACEGTK_H__ */
