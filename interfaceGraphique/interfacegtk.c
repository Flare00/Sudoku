#include "interfacegtk.h"

// constructeurMenus GLOBAUX
GtkBuilder *constructeurMenu;
GError *error = NULL;

// Fonction test print
static void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}

gboolean hide(GtkWidget *button, GdkEventButton *event, gpointer data)
{
	f_Menu *my_m = (f_Menu*) data;

  gtk_widget_hide(GTK_WIDGET (my_m->boutonJouer));
  gtk_widget_hide(GTK_WIDGET (my_m->boutonRegles));
  gtk_widget_hide(GTK_WIDGET (my_m->boutonOptions));
  gtk_widget_hide(GTK_WIDGET (my_m->boutonQuitter));

	return FALSE;
}

// Fonction Masquage Menu
// static void menuCacher(f_Menu *leMenu){
//     gtk_widget_hide(leMenu->boutonJouer);
// }

// Fonction Création Menu
static void menuCreer(f_Menu *leMenu){
  // Déclarations
  leMenu->fenetre = gtk_builder_get_object (constructeurMenu, "fenetre");
  leMenu->etiquetteTitre = gtk_builder_get_object (constructeurMenu, "etiquetteTitre");
  leMenu->boutonJouer = gtk_builder_get_object (constructeurMenu, "boutonJouer");
  leMenu->boutonRegles = gtk_builder_get_object (constructeurMenu, "boutonRegles");
  leMenu->boutonOptions = gtk_builder_get_object (constructeurMenu, "boutonOptions");
  leMenu->boutonQuitter = gtk_builder_get_object (constructeurMenu, "boutonQuitter");

  // Signaux
  g_signal_connect (leMenu->fenetre, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (leMenu->boutonJouer, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (leMenu->boutonRegles, "clicked", G_CALLBACK (hide), leMenu);
  g_signal_connect (leMenu->boutonOptions, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (leMenu->boutonQuitter, "clicked", G_CALLBACK (gtk_main_quit), NULL);

}



int main (int argc, char *argv[]){

  // Initialisation
  gtk_init (&argc, &argv);

  f_Menu *leMenu = (f_Menu*) malloc (sizeof (f_Menu));
  // Vérification du constructeurMenu (constructeurMenu.ui)
  constructeurMenu = gtk_builder_new ();
  if (gtk_builder_add_from_file (constructeurMenu, "builder.ui", &error) == 0){
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return 1;
  }

  // Menu
  menuCreer(leMenu);

  // Main Fonction GTK
  gtk_main ();

  return 0;
}
