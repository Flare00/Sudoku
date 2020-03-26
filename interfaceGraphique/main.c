#include "interfacegtk.h"


int main (int argc, char *argv[]){
  GError *erreur;
  //** GtkCssProvider *gtkCSS; **//

  // Initialisation GTK
  gtk_init (&argc, &argv);

  // Initialisation de la Structure
  b_Sudoku *bouton_Struct = (b_Sudoku*) malloc (sizeof (b_Sudoku));

  // Vérification du constructeur
  bouton_Struct->constructeur = gtk_builder_new ();
  if (gtk_builder_add_from_file (bouton_Struct->constructeur, "constructeur.ui", &erreur) == 0){
    g_printerr ("Erreur : chargement du constructeur: %s\n", erreur->message);
    g_clear_error (&erreur);
    return 1;
  }

  // Affectation de la structure
  grilleMenu = gtk_builder_get_object (bouton_Struct->constructeur, "grilleMenu");
  grilleDifficulte = gtk_builder_get_object (bouton_Struct->constructeur, "grilleDifficulte");
  grilleRegles = gtk_builder_get_object (bouton_Struct->constructeur, "grilleRegles");
  grilleOptions = gtk_builder_get_object (bouton_Struct->constructeur, "grilleOptions");
  grilleResoudre = gtk_builder_get_object (bouton_Struct->constructeur, "grilleResoudre");

  /** -- CSS PROBLEM --
  // Vérification du gtkCSS
  gtkCSS = gtk_css_provider_new();
  if (gtk_css_provider_load_from_path(gtkCSS, "themeSudoku.css", &erreur) == 0){
    g_printerr ("Erreur : chargement du CSS: %s\n", erreur->message);
    g_clear_error (&erreur);
    return 1;
  }
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(gtkCSS), GTK_STYLE_PROVIDER_PRIORITY_USER);
  **/

  // Initialisation de la fenetre principale
  fenetre = gtk_builder_get_object (bouton_Struct->constructeur, "fenetre");
  g_signal_connect (fenetre, "destroy", G_CALLBACK (gtk_main_quit), NULL);


  // Création des différentes parties du Menu
  menuCreer(bouton_Struct);
  difficulteCreer(bouton_Struct);
  reglesCreer(bouton_Struct);
  optionsCreer(bouton_Struct);
  resoudreCreer(bouton_Struct);


  // On envoie le menu en premier
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_widget_show_all(GTK_WIDGET (fenetre));

  // Main Fonction GTK
  gtk_main();

  return 0;
}
