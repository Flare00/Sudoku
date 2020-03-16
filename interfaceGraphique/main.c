#include "interfacegtk.h"

/** Fonction main() **/
int main (int argc, char *argv[]){

  // Initialisation GTK
  gtk_init (&argc, &argv);

  // Vérification du constructeur
  constructeur = gtk_builder_new ();
  if (gtk_builder_add_from_file (constructeur, "constructeur.ui", &erreur) == 0){
    g_printerr ("Erreur : chargement du constructeur: %s\n", erreur->message);
    g_clear_error (&erreur);
    return 1;
  }

  // Initialisation de la fenetre principale
  fenetre = gtk_builder_get_object (constructeur, "fenetre");
  g_signal_connect (fenetre, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  // Initialisation de la Structure
  b_Sudoku *bouton_Struct = (b_Sudoku*) malloc (sizeof (b_Sudoku));
  grilleMenu = gtk_builder_get_object (constructeur, "grilleMenu");
  grilleRegles = gtk_builder_get_object (constructeur, "grilleRegles");

  // Création des différentes parties du Menu
  menuCreer(bouton_Struct);
  reglesCreer(bouton_Struct);

  // On envoie le menu en premier
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_widget_show_all(GTK_WIDGET (fenetre));

  // Main Fonction GTK
  gtk_main();

  return 0;
}
