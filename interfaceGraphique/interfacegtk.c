#include "interfacegtk.h"
#include "sudokugtk.h"



/** Fonction transition **/
void transitionInterface(GtkWidget *widget, gpointer grille){
  g_object_ref(GTK_WIDGET (gtk_widget_get_ancestor (GTK_WIDGET (widget), GTK_TYPE_GRID)));
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (gtk_widget_get_ancestor (GTK_WIDGET (widget), GTK_TYPE_GRID)));
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grille));
  gtk_widget_show_all(GTK_WIDGET (fenetre));
}


/** Appel Sudoku **/
void appelSudoku(GtkWidget *widget, gpointer range){
  int val = gtk_range_get_value(range);
  g_object_ref(GTK_WIDGET (grilleResoudre));
  gtk_container_remove (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleResoudre));

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
      gtk_label_set_text(GTK_LABEL(etiquette), "\n4 x 4");
      break;

    case 2:
      gtk_label_set_text(GTK_LABEL(etiquette), "\n9 x 9");
      break;

    case 3:
      gtk_label_set_text(GTK_LABEL(etiquette), "\n16 x 16");
      break;

    case 4:
      gtk_label_set_text(GTK_LABEL(etiquette), "\n25 x 25");
      break;

    case 5:
      gtk_label_set_text(GTK_LABEL(etiquette), "\n36 x 36");
      break;

    case 6:
      gtk_label_set_text(GTK_LABEL(etiquette), "\n49 x 49");
      break;

    case 7:
      gtk_label_set_text(GTK_LABEL(etiquette), "\n64 x 64");
      break;

    default:
      gtk_label_set_text(GTK_LABEL(etiquette), "\n4 x 4");
  }
}


/** Fonction Création du choix de résolution du Sudoku **/
void resoudreCreer(){
  GtkAdjustment *ajustementHorizontal;
  GtkWidget *etiquetteResoudreTitre;
  GtkWidget *etiquetteResoudreTraduction;
  GtkWidget *scaleResoudreTaille;
  GtkWidget *boutonResoudreValider;
  GtkWidget *boutonResoudreRetour;

  ajustementHorizontal = gtk_adjustment_new (0, 1, 7, 1, 0, 0);
  etiquetteResoudreTitre = gtk_label_new ("Taille");
  etiquetteResoudreTraduction = gtk_label_new ("\n4 x 4");
  scaleResoudreTaille = gtk_scale_new (GTK_ORIENTATION_HORIZONTAL, ajustementHorizontal);
  boutonResoudreValider = gtk_button_new_with_label ("Valider");
  boutonResoudreRetour = gtk_button_new_with_label ("Retour");

  gtk_widget_set_name(etiquetteResoudreTitre, "titre");
  gtk_widget_set_name(etiquetteResoudreTraduction, "texte");
  gtk_widget_set_name(scaleResoudreTaille, "scale");
  gtk_widget_set_name(boutonResoudreValider, "bouton");
  gtk_widget_set_name(boutonResoudreRetour, "bouton");

  gtk_scale_set_digits (GTK_SCALE (scaleResoudreTaille), 0);
  gtk_widget_set_hexpand (scaleResoudreTaille, TRUE);
  gtk_widget_set_valign (scaleResoudreTaille, GTK_ALIGN_START);

  g_signal_connect (scaleResoudreTaille, "value-changed", G_CALLBACK (scaleTrad), etiquetteResoudreTraduction);
  g_signal_connect (boutonResoudreValider, "clicked", G_CALLBACK (appelSudoku), scaleResoudreTaille);
  g_signal_connect (boutonResoudreRetour, "clicked", G_CALLBACK (transitionInterface), grilleMenu);

  gtk_widget_set_margin_top (GTK_WIDGET (scaleResoudreTaille), 120);
  gtk_widget_set_margin_top (GTK_WIDGET (etiquetteResoudreTraduction), 120);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonResoudreValider), 30);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonResoudreRetour), 156);
  gtk_widget_set_margin_start (GTK_WIDGET (etiquetteResoudreTraduction), 15);


  gtk_grid_attach (GTK_GRID (grilleResoudre), GTK_WIDGET (etiquetteResoudreTitre), 0, 0, 5, 1);
  gtk_grid_attach (GTK_GRID (grilleResoudre), GTK_WIDGET (etiquetteResoudreTraduction), 1, 1, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleResoudre), GTK_WIDGET (scaleResoudreTaille), 2, 1, 2, 1);
  gtk_grid_attach (GTK_GRID (grilleResoudre), GTK_WIDGET (boutonResoudreValider), 2, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleResoudre), GTK_WIDGET (boutonResoudreRetour), 2, 3, 1, 1);
}


/** Fonction Création de l'interface des options **/
void optionsCreer(){
  GtkWidget *etiquetteOptionsTitre;
  GtkWidget *etiquetteOptionsDimension;
  GtkWidget *comboboxOptionsDimension;
  GtkWidget *boutonOptionsRetour;

  etiquetteOptionsTitre = gtk_label_new ("Options");
  etiquetteOptionsDimension = gtk_label_new ("Dimension");
  comboboxOptionsDimension = gtk_combo_box_text_new ();
  boutonOptionsRetour = gtk_button_new_with_label ("Retour");

  gtk_widget_set_name(etiquetteOptionsTitre, "titre");
  gtk_widget_set_name(etiquetteOptionsDimension, "texte");
  gtk_widget_set_name(boutonOptionsRetour, "bouton");

  const char *dimensionList[] = {"800 x 600", "1280 x 800", "1440 x 900", "1600 x 1000", "1920 x 1080"};
  for (int i = 0 ; i < G_N_ELEMENTS (dimensionList) ; i++){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comboboxOptionsDimension), dimensionList[i]);
  }
  gtk_combo_box_set_active (GTK_COMBO_BOX (comboboxOptionsDimension), 0);

  g_signal_connect (boutonOptionsRetour, "clicked", G_CALLBACK (transitionInterface), grilleMenu);
  g_signal_connect (comboboxOptionsDimension, "changed", G_CALLBACK (changementResolution), NULL);

  gtk_widget_set_margin_top (GTK_WIDGET (etiquetteOptionsDimension), 200);
  gtk_widget_set_margin_top (GTK_WIDGET (comboboxOptionsDimension), 200);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonOptionsRetour), 230);
  gtk_widget_set_margin_start (GTK_WIDGET (comboboxOptionsDimension), 15);

  gtk_grid_attach (GTK_GRID (grilleOptions), GTK_WIDGET (etiquetteOptionsTitre), 0, 0, 5, 2);
  gtk_grid_attach (GTK_GRID (grilleOptions), GTK_WIDGET (etiquetteOptionsDimension), 1, 2, 2, 1);
  gtk_grid_attach (GTK_GRID (grilleOptions), GTK_WIDGET (comboboxOptionsDimension), 3, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleOptions), GTK_WIDGET (boutonOptionsRetour), 2, 5, 1, 1);
}


/** Fonction Création de l'interface présentant les règles **/
void reglesCreer(){
  GtkWidget *etiquetteReglesTitre;
  GtkWidget *etiquetteReglesPresentation;
  GtkWidget *scrollReglesPresentation;
  GtkWidget *boutonReglesRetour;

  etiquetteReglesTitre = gtk_label_new ("Règles");
  etiquetteReglesPresentation = gtk_label_new ( "Le but du jeu dans le cas d'un sudoku classique, est de remplir ces cases avec des chiffres allant de 1 à 9 en veillant toujours à ce qu'un même chiffre ne figure qu'une seule fois par colonne, une seule fois par ligne, et une seule fois par carré de neuf cases.\n\n"
                                                "Au début du jeu, des chiffres sont déjà placés et il vous reste à trouver les autres. En effet, une grille initiale de sudoku correctement constituée ne peut aboutir qu'à une et une seule solution. Pour trouver les chiffres manquants, tout est une question de logique et d'observation.\n\n"
                                                "Un sudoku classique contient neuf lignes et neuf colonnes, donc 81 cases au total. Mais il existe de nombreuses variantes au sudoku classique (aussi appelé 9x9), ne serait-ce qu'en modifiant le nombre de lignes et de colonnes. Vous pouvez ainsi trouver sur Le Sudoku toute la combinaison des grilles en allant du sudoku enfant 4x4 au sudoku géant 12x12.\n\n"
                                                "Voici la liste des caractères acceptés en fonction de la taille du Sudoku :\n"
                                                "4x4 :    {1,2,3,4}\n"
                                                "9x9 :    {1,2,3,4,5,6,7,8,9}\n"
                                                "16x16 :  {1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G}\n"
                                                "25x25 :  {1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P}\n"
                                                "36x36 :  {1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a}\n"
                                                "49x49 :  {1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n}\n"
                                                "64x64 :  {1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,@,&,+}\n"
                                              );
  scrollReglesPresentation = gtk_scrolled_window_new (NULL, NULL);
  boutonReglesRetour = gtk_button_new_with_label ("Retour");

  gtk_widget_set_name(etiquetteReglesTitre, "titre");
  gtk_widget_set_name(etiquetteReglesPresentation, "regle");
  gtk_widget_set_name(boutonReglesRetour, "bouton");

  gtk_container_set_border_width (GTK_CONTAINER (scrollReglesPresentation), 10);
  gtk_container_add (GTK_CONTAINER (scrollReglesPresentation), GTK_WIDGET (etiquetteReglesPresentation));
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollReglesPresentation), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_label_set_line_wrap (GTK_LABEL (etiquetteReglesPresentation), TRUE);
  g_signal_connect (boutonReglesRetour, "clicked", G_CALLBACK (transitionInterface), grilleMenu);

  gtk_widget_set_vexpand (GTK_WIDGET (scrollReglesPresentation), TRUE);

  gtk_widget_set_margin_bottom (GTK_WIDGET (scrollReglesPresentation), 15);
  gtk_widget_set_margin_top (GTK_WIDGET (scrollReglesPresentation), 50);
  gtk_widget_set_margin_start (GTK_WIDGET (scrollReglesPresentation), 25);
  gtk_widget_set_margin_end (GTK_WIDGET (scrollReglesPresentation), 25);
  gtk_widget_set_margin_bottom (GTK_WIDGET (boutonReglesRetour), 51);


  gtk_grid_attach (GTK_GRID (grilleRegles), GTK_WIDGET (etiquetteReglesTitre), 0, 0, 3, 2);
  gtk_grid_attach (GTK_GRID (grilleRegles), GTK_WIDGET (scrollReglesPresentation), 0, 2, 3, 4);
  gtk_grid_attach (GTK_GRID (grilleRegles), GTK_WIDGET (boutonReglesRetour), 1, 6, 1, 1);
}


/** Fonction Création de l'interface du choix de la difficulté **/
void difficulteCreer(){
  GtkWidget *etiquetteDifficulteTitre;
  GtkWidget *boutonDifficulteFacile;
  GtkWidget *boutonDifficulteNormal;
  GtkWidget *boutonDifficulteDifficile;
  GtkWidget *boutonDifficulteExpert;
  GtkWidget *boutonDifficulteRetour;

  etiquetteDifficulteTitre = gtk_label_new ("Niveau");
  boutonDifficulteFacile = gtk_button_new_with_label ("Facile");
  boutonDifficulteNormal = gtk_button_new_with_label ("Normal");
  boutonDifficulteDifficile = gtk_button_new_with_label ("Difficile");
  boutonDifficulteExpert = gtk_button_new_with_label ("Expert");
  boutonDifficulteRetour = gtk_button_new_with_label ("Retour");

  gtk_widget_set_name(etiquetteDifficulteTitre, "titre");
  gtk_widget_set_name(boutonDifficulteFacile, "bouton");
  gtk_widget_set_name(boutonDifficulteNormal, "bouton");
  gtk_widget_set_name(boutonDifficulteDifficile, "bouton");
  gtk_widget_set_name(boutonDifficulteExpert, "bouton");
  gtk_widget_set_name(boutonDifficulteRetour, "bouton");

  g_signal_connect (boutonDifficulteFacile, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (boutonDifficulteNormal, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (boutonDifficulteDifficile, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (boutonDifficulteExpert, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect (boutonDifficulteRetour, "clicked", G_CALLBACK (transitionInterface), grilleMenu);

  gtk_widget_set_margin_top (GTK_WIDGET (boutonDifficulteFacile), 120);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonDifficulteNormal), 30);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonDifficulteDifficile), 30);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonDifficulteExpert), 30);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonDifficulteRetour), 130);

  gtk_grid_attach (GTK_GRID (grilleDifficulte), GTK_WIDGET (etiquetteDifficulteTitre), 0, 0, 3, 2);
  gtk_grid_attach (GTK_GRID (grilleDifficulte), GTK_WIDGET (boutonDifficulteFacile), 1, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleDifficulte), GTK_WIDGET (boutonDifficulteNormal), 1, 3, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleDifficulte), GTK_WIDGET (boutonDifficulteDifficile), 1, 4, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleDifficulte), GTK_WIDGET (boutonDifficulteExpert), 1, 5, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleDifficulte), GTK_WIDGET (boutonDifficulteRetour), 1, 6, 1, 1);
}


/** Fonction Création du Menu **/
void menuCreer(){
  GtkWidget *etiquetteMenuTitre;
  GtkWidget *boutonMenuJouer;
  GtkWidget *boutonMenuResoudre;
  GtkWidget *boutonMenuRegles;
  GtkWidget *boutonMenuOptions;
  GtkWidget *boutonMenuQuitter;

  etiquetteMenuTitre = gtk_label_new ("Sudoku");
  boutonMenuJouer = gtk_button_new_with_label ("Jouer");
  boutonMenuResoudre = gtk_button_new_with_label ("Résoudre");
  boutonMenuRegles = gtk_button_new_with_label ("Règles");
  boutonMenuOptions = gtk_button_new_with_label ("Options");
  boutonMenuQuitter = gtk_button_new_with_label ("Quitter");

  gtk_widget_set_name(etiquetteMenuTitre, "titre");
  gtk_widget_set_name(boutonMenuJouer, "bouton");
  gtk_widget_set_name(boutonMenuResoudre, "bouton");
  gtk_widget_set_name(boutonMenuRegles, "bouton");
  gtk_widget_set_name(boutonMenuOptions, "bouton");
  gtk_widget_set_name(boutonMenuQuitter, "bouton");

  g_signal_connect (boutonMenuJouer, "clicked", G_CALLBACK (transitionInterface), grilleDifficulte);
  g_signal_connect (boutonMenuResoudre, "clicked", G_CALLBACK (transitionInterface), grilleResoudre);
  g_signal_connect (boutonMenuRegles, "clicked", G_CALLBACK (transitionInterface), grilleRegles);
  g_signal_connect (boutonMenuOptions, "clicked", G_CALLBACK (transitionInterface), grilleOptions);
  g_signal_connect (boutonMenuQuitter, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_set_margin_top (GTK_WIDGET (boutonMenuJouer), 120);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonMenuResoudre), 30);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonMenuRegles), 30);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonMenuOptions), 30);
  gtk_widget_set_margin_top (GTK_WIDGET (boutonMenuQuitter), 130);

  gtk_grid_attach (GTK_GRID (grilleMenu), GTK_WIDGET (etiquetteMenuTitre), 0, 0, 3, 2);
  gtk_grid_attach (GTK_GRID (grilleMenu), GTK_WIDGET (boutonMenuJouer), 1, 2, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleMenu), GTK_WIDGET (boutonMenuResoudre), 1, 3, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleMenu), GTK_WIDGET (boutonMenuRegles), 1, 4, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleMenu), GTK_WIDGET (boutonMenuOptions), 1, 5, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleMenu), GTK_WIDGET (boutonMenuQuitter), 1, 6, 1, 1);
}


/** Fonction Création Grille **/
void grilleCreer(GtkWidget *grille){
  gtk_grid_set_column_homogeneous (GTK_GRID (grille), TRUE);
  gtk_widget_set_name(grille, "fenetre");
}


/** Fonction CSS **/
void myCSS(){
  GtkCssProvider *gtkCSS;
  GdkDisplay *affichage;
  GdkScreen *ecran;
  GError *erreur = NULL;

  const gchar *cheminCSS = "themeSudoku.css";
  GFile *fichierCSS = g_file_new_for_path(cheminCSS);
  gtkCSS = gtk_css_provider_new();
  affichage = gdk_display_get_default();
  ecran = gdk_display_get_default_screen (affichage);
  gtk_style_context_add_provider_for_screen (ecran, GTK_STYLE_PROVIDER(gtkCSS), GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_css_provider_load_from_file(gtkCSS, fichierCSS, &erreur);
  if(erreur){
    g_warning ("Erreur chargement CSS :\n %s", erreur->message);
    g_clear_error (&erreur);
  }

  g_object_unref (fichierCSS);
}
