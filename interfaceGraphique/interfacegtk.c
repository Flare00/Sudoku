#include "interfacegtk.h"

// constructeurMenus GLOBAUX
GtkBuilder *constructeurMenu;
GError *error = NULL;

// Fonction test print
static void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}

// Fonction Menu
static void createMenu(){
    // Widgets
    GObject *fenetre;
    GObject *etiquetteTitre;
    GObject *boutonJouer;
    GObject *boutonRegles;
    GObject *boutonOptions;
    GObject *boutonQuitter;

    // Déclarations
    fenetre = gtk_builder_get_object (constructeurMenu, "fenetre");
    etiquetteTitre = gtk_builder_get_object (constructeurMenu, "etiquetteTitre");
    boutonJouer = gtk_builder_get_object (constructeurMenu, "boutonJouer");
    boutonRegles = gtk_builder_get_object (constructeurMenu, "boutonRegles");
    boutonOptions = gtk_builder_get_object (constructeurMenu, "boutonOptions");
    boutonQuitter = gtk_builder_get_object (constructeurMenu, "boutonQuitter");

    // Signaux
    g_signal_connect (fenetre, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (boutonJouer, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect (boutonQuitter, "clicked", G_CALLBACK (gtk_main_quit), NULL);
}


int main (int argc, char *argv[]){

  // Initialisation
  gtk_init (&argc, &argv);

  // Vérification du constructeurMenu (constructeurMenu.ui)
  constructeurMenu = gtk_builder_new ();
  if (gtk_builder_add_from_file (constructeurMenu, "builder.ui", &error) == 0){
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return 1;
  }

  // Menu
  createMenu();

  // Main Fonction GTK
  gtk_main ();

  return 0;
}
