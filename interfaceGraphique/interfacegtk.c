#include "interfacegtk.h"


/** Fonction HelloWorld Test **/
void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}


/** Fonction transition du menu aux règles **/
void transitionMenuRegles(){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleRegles));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction transition des règles au menu **/
void transitionReglesMenu(){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleRegles));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction transition du menu aux options **/
void transitionMenuOptions(){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleOptions));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction transition des options au menu **/
void transitionOptionsMenu(){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleOptions));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction Création Règles **/
void reglesCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonRetourRegles = gtk_builder_get_object (constructeur, "boutonRetourRegles");
  g_signal_connect (bouton_Struct->boutonRetourRegles, "clicked", G_CALLBACK (transitionReglesMenu), NULL);
}


/** Fonction Création Règles **/
void optionsCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->switchResolution = gtk_builder_get_object (constructeur, "switchResolution");
  bouton_Struct->switchSurlignerNombre = gtk_builder_get_object (constructeur, "switchSurlignerNombre");
  bouton_Struct->switchSurlignerZone = gtk_builder_get_object (constructeur, "switchSurlignerZone");
  bouton_Struct->boutonRetourOptions = gtk_builder_get_object (constructeur, "boutonRetourOptions");
  g_signal_connect (bouton_Struct->boutonRetourOptions, "clicked", G_CALLBACK (transitionOptionsMenu), NULL);
}


/** Fonction Création Menu **/
void menuCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonJouer = gtk_builder_get_object (constructeur, "boutonJouer");
  bouton_Struct->boutonResolution = gtk_builder_get_object (constructeur, "boutonResolution");
  bouton_Struct->boutonRegles = gtk_builder_get_object (constructeur, "boutonRegles");
  bouton_Struct->boutonOptions = gtk_builder_get_object (constructeur, "boutonOptions");
  bouton_Struct->boutonQuitter = gtk_builder_get_object (constructeur, "boutonQuitter");
  g_signal_connect (bouton_Struct->boutonJouer, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonResolution, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonRegles, "clicked", G_CALLBACK (transitionMenuRegles), NULL);
  g_signal_connect (bouton_Struct->boutonOptions, "clicked", G_CALLBACK (transitionMenuOptions), NULL);
  g_signal_connect (bouton_Struct->boutonQuitter, "clicked", G_CALLBACK (gtk_main_quit), NULL);
}
