#include "interfacegtk.h"
#include "sudokugtk.h"


/** Appel Sudoku **/
void appelSudoku(GtkRange *widget, gpointer range){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleResoudre));
  int val = gtk_range_get_value(range);

  switch (val){
    case 1:
      sudokuCreer(4);
      break;

    case 2:
      sudokuCreer(9);
      break;

    case 3:
      sudokuCreer(16);
      break;

    case 4:
      sudokuCreer(25);
      break;

    case 5:
      sudokuCreer(36);
      break;

    case 6:
      sudokuCreer(49);
      break;

    case 7:
      sudokuCreer(64);
      break;

    default:
      sudokuCreer(4);
  }

  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction transition **/
void transitionInterface(GtkWidget *widget, gpointer grille){
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (gtk_widget_get_ancestor (GTK_WIDGET (widget), GTK_TYPE_GRID)));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grille));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Fonction résolution fenêtre principale **/
void changementResolution(GtkComboBox *widget){

  switch (gtk_combo_box_get_active (widget)){
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


/** Fonction Traduction Slide **/
void scaleTrad(GtkRange *widget, gpointer etiquette){
  int val = gtk_range_get_value(widget);

  switch (val){
    case 1:
      gtk_label_set_text(GTK_LABEL(etiquette), "4 x 4");
      break;

    case 2:
      gtk_label_set_text(GTK_LABEL(etiquette), "9 x 9");
      break;

    case 3:
      gtk_label_set_text(GTK_LABEL(etiquette), "16 x 16");
      break;

    case 4:
      gtk_label_set_text(GTK_LABEL(etiquette), "25 x 25");
      break;

    case 5:
      gtk_label_set_text(GTK_LABEL(etiquette), "36 x 36");
      break;

    case 6:
      gtk_label_set_text(GTK_LABEL(etiquette), "49 x 49");
      break;

    case 7:
      gtk_label_set_text(GTK_LABEL(etiquette), "64 x 64");
      break;

    default:
      gtk_label_set_text(GTK_LABEL(etiquette), "4 x 4");
  }
}



// ---- !!! ---- A OPTIMISER  ---- !!! ---- //
void changementSurligner(GObject *switcher, GParamSpec *pspec, gpointer user_data){
  if (gtk_switch_get_active (GTK_SWITCH (switcher))){
    g_print("yes!");
  }
  else{
    g_print("no!");
  }
}


// ---- !!! ---- A OPTIMISER  ---- !!! ---- //
/** Fonction Création Résoudre **/
void resoudreCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonRetourResoudre = gtk_builder_get_object (bouton_Struct->constructeur, "boutonRetourResoudre");
  bouton_Struct->boutonValiderResoudre = gtk_builder_get_object (bouton_Struct->constructeur, "boutonValiderResoudre");
  bouton_Struct->scaleSudokuResoudre = gtk_builder_get_object (bouton_Struct->constructeur, "scaleSudokuResoudre");
  bouton_Struct->etiquetteTraductionResoudre = gtk_builder_get_object (bouton_Struct->constructeur, "etiquetteTraductionResoudre");
  g_signal_connect (bouton_Struct->scaleSudokuResoudre, "value-changed", G_CALLBACK (scaleTrad), bouton_Struct->etiquetteTraductionResoudre);
  g_signal_connect (bouton_Struct->boutonValiderResoudre, "clicked", G_CALLBACK (appelSudoku), bouton_Struct->scaleSudokuResoudre);
  g_signal_connect (bouton_Struct->boutonRetourResoudre, "clicked", G_CALLBACK (transitionInterface), grilleMenu);
}


// ---- !!! ---- A OPTIMISER  ---- !!! ---- //
/** Fonction Création Règles **/
void reglesCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonRetourRegles = gtk_builder_get_object (bouton_Struct->constructeur, "boutonRetourRegles");
  g_signal_connect (bouton_Struct->boutonRetourRegles, "clicked", G_CALLBACK (transitionInterface), grilleMenu);
}


// ---- !!! ---- A OPTIMISER  ---- !!! ---- //
/** Fonction Création Options **/
void optionsCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->switchResolution = gtk_builder_get_object (bouton_Struct->constructeur, "switchResolution");
  bouton_Struct->switchSurlignerNombre = gtk_builder_get_object (bouton_Struct->constructeur, "switchSurlignerNombre");
  bouton_Struct->switchSurlignerZone = gtk_builder_get_object (bouton_Struct->constructeur, "switchSurlignerZone");
  bouton_Struct->boutonRetourOptions = gtk_builder_get_object (bouton_Struct->constructeur, "boutonRetourOptions");
  g_signal_connect (bouton_Struct->switchResolution, "changed", G_CALLBACK (changementResolution), NULL);
  g_signal_connect (bouton_Struct->switchSurlignerNombre, "notify::active", G_CALLBACK (changementSurligner), NULL);
  g_signal_connect (bouton_Struct->switchSurlignerZone, "notify::active", G_CALLBACK (changementSurligner), NULL);
  g_signal_connect (bouton_Struct->boutonRetourOptions, "clicked", G_CALLBACK (transitionInterface), grilleMenu);
}


// ---- !!! ---- A OPTIMISER  ---- !!! ---- //
/** Fonction Création Difficulte **/
void difficulteCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonFacileDifficulte = gtk_builder_get_object (bouton_Struct->constructeur, "boutonFacileDifficulte");
  bouton_Struct->boutonNormalDifficulte = gtk_builder_get_object (bouton_Struct->constructeur, "boutonNormalDifficulte");
  bouton_Struct->boutonDifficileDifficulte = gtk_builder_get_object (bouton_Struct->constructeur, "boutonDifficileDifficulte");
  bouton_Struct->boutonExpertDifficulte = gtk_builder_get_object (bouton_Struct->constructeur, "boutonExpertDifficulte");
  bouton_Struct->boutonRetourDifficulte = gtk_builder_get_object (bouton_Struct->constructeur, "boutonRetourDifficulte");
  g_signal_connect (bouton_Struct->boutonFacileDifficulte, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonNormalDifficulte, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonDifficileDifficulte, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonExpertDifficulte, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (bouton_Struct->boutonRetourDifficulte, "clicked", G_CALLBACK (transitionInterface), grilleMenu);
}


// ---- !!! ---- A OPTIMISER  ---- !!! ---- //
/** Fonction Création Menu **/
void menuCreer(b_Sudoku *bouton_Struct){

  // Déclarations et Signaux des boutons
  bouton_Struct->boutonJouer = gtk_builder_get_object (bouton_Struct->constructeur, "boutonJouer");
  bouton_Struct->boutonResolution = gtk_builder_get_object (bouton_Struct->constructeur, "boutonResolution");
  bouton_Struct->boutonRegles = gtk_builder_get_object (bouton_Struct->constructeur, "boutonRegles");
  bouton_Struct->boutonOptions = gtk_builder_get_object (bouton_Struct->constructeur, "boutonOptions");
  bouton_Struct->boutonQuitter = gtk_builder_get_object (bouton_Struct->constructeur, "boutonQuitter");
  g_signal_connect (bouton_Struct->boutonJouer, "clicked", G_CALLBACK (transitionInterface), grilleDifficulte);
  g_signal_connect (bouton_Struct->boutonResolution, "clicked", G_CALLBACK (transitionInterface), grilleResoudre);
  g_signal_connect (bouton_Struct->boutonRegles, "clicked", G_CALLBACK (transitionInterface), grilleRegles);
  g_signal_connect (bouton_Struct->boutonOptions, "clicked", G_CALLBACK (transitionInterface), grilleOptions);
  g_signal_connect (bouton_Struct->boutonQuitter, "clicked", G_CALLBACK (gtk_main_quit), NULL);
}
