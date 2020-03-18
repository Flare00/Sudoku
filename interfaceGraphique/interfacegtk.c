#include "interfacegtk.h"
#include "sudokugtk.h"


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


/** Fonction transition de la difficulte au menu **/
void transitionDifficulteMenu(){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleDifficulte));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction transition du menu à la difficulte **/
void transitionMenuDifficulte(){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleMenu));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleDifficulte));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction changement résolution fenetre **/
void changementResolution(GtkComboBox *widget, gpointer user_data){
  GtkComboBox *combo_box = widget;

  switch (gtk_combo_box_get_active (combo_box)){
    case 1:
      gtk_window_resize(GTK_WINDOW(fenetre), 1280, 800);
      break;

    case 2:
      gtk_window_resize(GTK_WINDOW(fenetre), 1440, 900);
      break;

    case 3:
      gtk_window_resize(GTK_WINDOW(fenetre), 1600, 1000);
      break;

    case 4:
      gtk_window_resize(GTK_WINDOW(fenetre), 1920, 1080);
      break;

    default:
      gtk_window_resize(GTK_WINDOW(fenetre), 800, 600);
    }
    gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER_ALWAYS);
}


/** Fonction changement résolution fenetre **/
void changementSurligner(GObject *switcher, GParamSpec *pspec, gpointer user_data){
  if (gtk_switch_get_active (GTK_SWITCH (switcher))){
    g_print("yes!");
  }
  else{
    g_print("no!");
  }
}


/** Fonction Création Règles **/
void reglesCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonRetourRegles = gtk_builder_get_object (constructeur, "boutonRetourRegles");
  g_signal_connect (bouton_Struct->boutonRetourRegles, "clicked", G_CALLBACK (transitionReglesMenu), NULL);
}


/** Fonction Création Options **/
void optionsCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->switchResolution = gtk_builder_get_object (constructeur, "switchResolution");
  bouton_Struct->switchSurlignerNombre = gtk_builder_get_object (constructeur, "switchSurlignerNombre");
  bouton_Struct->switchSurlignerZone = gtk_builder_get_object (constructeur, "switchSurlignerZone");
  bouton_Struct->boutonRetourOptions = gtk_builder_get_object (constructeur, "boutonRetourOptions");
  g_signal_connect (bouton_Struct->switchResolution, "changed", G_CALLBACK (changementResolution), NULL);
  g_signal_connect (bouton_Struct->switchSurlignerNombre, "notify::active", G_CALLBACK (changementSurligner), NULL);
  g_signal_connect (bouton_Struct->switchSurlignerZone, "notify::active", G_CALLBACK (changementSurligner), NULL);
  g_signal_connect (bouton_Struct->boutonRetourOptions, "clicked", G_CALLBACK (transitionOptionsMenu), NULL);
}


/** Fonction Création Difficulte **/
void difficulteCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonFacileDifficulte = gtk_builder_get_object (constructeur, "boutonFacileDifficulte");
  bouton_Struct->boutonNormalDifficulte = gtk_builder_get_object (constructeur, "boutonNormalDifficulte");
  bouton_Struct->boutonDifficileDifficulte = gtk_builder_get_object (constructeur, "boutonDifficileDifficulte");
  bouton_Struct->boutonExpertDifficulte = gtk_builder_get_object (constructeur, "boutonExpertDifficulte");
  bouton_Struct->boutonRetourDifficulte = gtk_builder_get_object (constructeur, "boutonRetourDifficulte");
  g_signal_connect (bouton_Struct->boutonFacileDifficulte, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonNormalDifficulte, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonDifficileDifficulte, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonExpertDifficulte, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonRetourDifficulte, "clicked", G_CALLBACK (transitionDifficulteMenu), NULL);
}


/** Fonction Création Menu **/
void menuCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonJouer = gtk_builder_get_object (constructeur, "boutonJouer");
  bouton_Struct->boutonResolution = gtk_builder_get_object (constructeur, "boutonResolution");
  bouton_Struct->boutonRegles = gtk_builder_get_object (constructeur, "boutonRegles");
  bouton_Struct->boutonOptions = gtk_builder_get_object (constructeur, "boutonOptions");
  bouton_Struct->boutonQuitter = gtk_builder_get_object (constructeur, "boutonQuitter");
  g_signal_connect (bouton_Struct->boutonJouer, "clicked", G_CALLBACK (transitionMenuDifficulte), NULL);
  g_signal_connect (bouton_Struct->boutonResolution, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonRegles, "clicked", G_CALLBACK (transitionMenuRegles), NULL);
  g_signal_connect (bouton_Struct->boutonOptions, "clicked", G_CALLBACK (transitionMenuOptions), NULL);
  g_signal_connect (bouton_Struct->boutonQuitter, "clicked", G_CALLBACK (gtk_main_quit), NULL);
}
