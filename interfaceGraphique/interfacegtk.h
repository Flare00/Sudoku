#ifndef __INTERFACEGTK_H__
#define __INTERFACEGTK_H__

#include <gtk/gtk.h>
G_BEGIN_DECLS

void  quit();
/**
  * Widgets Globaux (Grilles et Fenêtre).
  */
GtkWidget *fenetre;
GtkWidget *grilleMenu;
GtkWidget *grilleDifficulte;
GtkWidget *grilleRegles;
GtkWidget *grilleOptions;
GtkWidget *grilleResoudre;


/**
 * @brief Création de l'interface "Menu".
 *
 * @return void         Interface "Menu" initialisée sur la grille "grilleMenu".
 */
void menuCreer();


/**
 * @brief Création de l'interface "Difficulte".
 *
 * @return void         Interface "Difficulte" initialisée sur la grille "grilleDifficulte".
 */
void difficulteCreer();


/**
 * @brief Création de l'interface "Regles".
 *
 * @return void         Interface "Regles" initialisée sur la grille "grilleRegles".
 */
void reglesCreer();


/**
 * @brief Création de l'interface "Options".
 *
 * @return void         Interface "Options" initialisée sur la grille "grilleOptions".
 */
void optionsCreer();


/**
 * @brief Création de l'interface "Résoudre".
 *
 * @return void         Interface "Résoudre" initialisée sur la grille "grilleResoudre".
 */
void resoudreCreer();


/**
 * @brief Configuration de l'homogénéité et du CSS de la grille.
 *
 * @param grille        Grille à configurer.
 * @return void         Grille homogénéisé avec CSS.
 */
void grilleConfiguration(GtkWidget *grille);


/**
 * @brief Transitions entre les différentes interfaces possibles.
 *
 * @param widget        Bouton appelant.
 * @param grille        Grille à afficher.
 * @return void         Affichage de la grille paramètre dans la fenêtre principale.
 */
void transitionInterface(GtkWidget *widget, gpointer grille);


/**
 * @brief Changement de résolution de la fenêtre principale.
 *
 * @param widget        Liste appelante.
 * @return void         Redimension de la fenêtre principale.
 */
void changementResolution(GtkComboBox *widget);


/**
 * @brief Traduction du widget Scale en Taille sudoku n*n dans l'étiquette.
 *
 * @param widget        Scale appelant.
 * @param etiquette     Etiquette permettant l'affichage de la Traduction.
 * @return void         Retranscription du Scale dans le widget etiquette.
 */
void scaleTrad(GtkRange *widget, gpointer etiquette);


/**
 * @brief Permet une configuration de l'appel de la fonction Sudoku en fonction de l'interface.
 *
 * @param widget        Bouton appelant.
 * @param range         Scale permettant de savoir quelle taille utiliser.
 * @return void         Envoi de la fonction Sudoku.
 */
void appelSudoku(GtkWidget *widget, gpointer range);


/**
 * @brief configuration du CSS dans GTK.
 *
 * @return void
 */
void myCSS();


G_END_DECLS

#endif /* __INTERFACEGTK_H__ */
