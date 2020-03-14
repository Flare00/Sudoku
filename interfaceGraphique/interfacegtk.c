#include "interfacegtk.h"

// constructeurs GLOBAUX
GtkBuilder *constructeur;
GObject *fenetre;
GError *erreur = NULL;

/** Fonction test **/
static void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}

/** Fonction Masquage Menu **/
gboolean menuCacher (GtkWidget *button, GdkEventButton *event, gpointer data){

  // Passage de la Structure
	f_Menu *my_m = (f_Menu*) data;

  // Fonction hide
  gtk_widget_hide(GTK_WIDGET (my_m->boutonJouer));
  gtk_widget_hide(GTK_WIDGET (my_m->boutonRegles));
  gtk_widget_hide(GTK_WIDGET (my_m->boutonOptions));
  gtk_widget_hide(GTK_WIDGET (my_m->boutonQuitter));

	return FALSE;
}

/** Fonction Création Menu **/
static void menuCreer(f_Menu *leMenu){

  // Reception de la grille dans la Fenetre
  leMenu->grilleMenu = gtk_builder_get_object (constructeur, "grilleMenu");
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (leMenu->grilleMenu));

  // Déclarations
  leMenu->etiquetteTitre = gtk_builder_get_object (constructeur, "etiquetteTitre");
  leMenu->boutonJouer = gtk_builder_get_object (constructeur, "boutonJouer");
  leMenu->boutonRegles = gtk_builder_get_object (constructeur, "boutonRegles");
  leMenu->boutonOptions = gtk_builder_get_object (constructeur, "boutonOptions");
  leMenu->boutonQuitter = gtk_builder_get_object (constructeur, "boutonQuitter");

  // Signaux
  g_signal_connect (leMenu->boutonJouer, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (leMenu->boutonRegles, "clicked", G_CALLBACK (menuCacher), leMenu);
  g_signal_connect (leMenu->boutonOptions, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (leMenu->boutonQuitter, "clicked", G_CALLBACK (gtk_main_quit), NULL);
}


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

  // Initialisation Fenetre & Structures
  fenetre = gtk_builder_get_object (constructeur, "fenetre");
  f_Menu *leMenu = (f_Menu*) malloc (sizeof (f_Menu));

  // Afficher le Menu
  menuCreer(leMenu);

  // Main Fonction GTK
  gtk_main ();

  return 0;
}
