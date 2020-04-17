#include "interfacegtk.h"


int main (int argc, char *argv[]){
  // Initialisation GTK
  gtk_init (&argc, &argv);

  // Chargement du CSS
  myCSS();

  // Initialisation de la fenetre principale
  fenetre = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (fenetre), "Sudoku");
  gtk_widget_set_size_request (GTK_WIDGET (fenetre), 800, 600);
  gtk_window_set_position (GTK_WINDOW (fenetre), GTK_WIN_POS_CENTER_ALWAYS);
  g_signal_connect (fenetre, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  // Initialisation des Grilles
  grilleMenu = gtk_grid_new();
  grilleDifficulte = gtk_grid_new();
  grilleRegles = gtk_grid_new();
  grilleOptions = gtk_grid_new();
  grilleResoudre = gtk_grid_new();
  grilleConfiguration(grilleMenu);
  grilleConfiguration(grilleDifficulte);
  grilleConfiguration(grilleRegles);
  grilleConfiguration(grilleOptions);
  grilleConfiguration(grilleResoudre);

  // Création des différentes parties de l'interface
  menuCreer();
  difficulteCreer();
  reglesCreer();
  optionsCreer();
  resoudreCreer();

  // Affichage du Menu
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_widget_show_all(GTK_WIDGET (fenetre));

  // Main Fonction GTK
  gtk_main();

  return 0;
}
