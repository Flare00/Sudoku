#include "interfacegtk.h"


// Widgets GLOBAUX
GtkBuilder *constructeur;
GObject *fenetre;
GObject *grilleMenu;
GObject *grilleRegles;
GError *erreur = NULL;


/** Fonction HelloWorld Test **/
static void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}


/** Fonction transition du menu aux règles **/
static void transitionMenuRegles(){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleRegles));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction transition des règles au menu **/
static void transitionReglesMenu(){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleRegles));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction Création Règles **/
static void reglesCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonRetourRegles = gtk_builder_get_object (constructeur, "boutonRetourRegles");
  g_signal_connect (bouton_Struct->boutonRetourRegles, "clicked", G_CALLBACK (transitionReglesMenu), NULL);
}


/** Fonction Création Menu **/
static void menuCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonJouer = gtk_builder_get_object (constructeur, "boutonJouer");
  bouton_Struct->boutonRegles = gtk_builder_get_object (constructeur, "boutonRegles");
  bouton_Struct->boutonOptions = gtk_builder_get_object (constructeur, "boutonOptions");
  bouton_Struct->boutonQuitter = gtk_builder_get_object (constructeur, "boutonQuitter");
  g_signal_connect (bouton_Struct->boutonJouer, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonRegles, "clicked", G_CALLBACK (transitionMenuRegles), NULL);
  g_signal_connect (bouton_Struct->boutonOptions, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonQuitter, "clicked", G_CALLBACK (gtk_main_quit), NULL);
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
