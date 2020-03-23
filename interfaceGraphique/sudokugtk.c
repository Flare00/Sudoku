#include "sudokugtk.h"
#include "interfacegtk.h"

/** Fonction HelloWorld Test **/
void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}

/** Fonction vérification des entrées **/
void enter_callback(GtkEntry *widget, GdkEvent *event, gpointer tailleSudoku){
  GtkEntry *entry_widget = widget;
  const gchar *entry_text;
  const char *caracDispo[64] = {"1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","@","&","+"};
  char trouve = 0; // bool optimisé
  int taille = GPOINTER_TO_INT(tailleSudoku);

  entry_text = gtk_entry_get_text (GTK_ENTRY (entry_widget));
  for(int i = 0 ; i<taille && trouve == 0 ; i++){
    if(strcmp(entry_text, caracDispo[i]) == 0){
      printf ("Entry contents: %s\n", entry_text);
      trouve = 1;
    }
  }
  if(!trouve){ gtk_entry_set_text (GTK_ENTRY (entry_widget), ""); }
}

/** Fonction création du Sudoku **/
void sudokuCreer(int taille){
  GtkWidget *grilleBoutonJeu;
  GtkWidget *grilleSudoku;
  GtkWidget *caseSudoku[taille][taille];
  GtkWidget *scrollSudoku;
  GtkWidget *jeuRetour;
  GtkWidget *jeuVerification;
  GtkWidget *jeuEtiquetteTitre;

  // Grille des Boutons du Jeu
  grilleBoutonJeu = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleBoutonJeu));

  // Boutons exemples
  jeuEtiquetteTitre = gtk_label_new ("Entrez le Sudoku à résoudre");
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuEtiquetteTitre), 0, 0, 5, 1);

  jeuRetour = gtk_button_new_with_label ("Retour Menu");
  g_signal_connect (jeuRetour, "clicked", G_CALLBACK (transitionInterface), grilleMenu);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuRetour), 0, 3, 1, 1);

  jeuVerification = gtk_button_new_with_label ("Vérification");
  g_signal_connect (jeuVerification, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (jeuVerification, "clicked", G_CALLBACK (gtk_widget_destroy), fenetre);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuVerification), 4, 3, 1, 1);

  // Scroll du SUDOKU
  scrollSudoku = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_set_border_width (GTK_CONTAINER (scrollSudoku), 20);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollSudoku), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_set_vexpand (GTK_WIDGET (scrollSudoku), TRUE);
  gtk_widget_set_hexpand (GTK_WIDGET (scrollSudoku), TRUE);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (scrollSudoku), 0, 1, 5, 2);

  // Grille du SUDOKU
  grilleSudoku = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (scrollSudoku), grilleSudoku);

  // Construction des cases du Sudoku dans la grille
  for (int i = 0; i < taille; i++){
    for (int j = 0; j < taille; j++){
      // Création "Entry" - Taille char max - Texte - Align center - Taille pour 1 Char - Taille Carré - Margin - Placement
      caseSudoku[i][j] = gtk_entry_new ();
      gtk_entry_set_max_length (GTK_ENTRY (caseSudoku[i][j]), 1);
      gtk_entry_set_placeholder_text (GTK_ENTRY (caseSudoku[i][j]), "0");
      gtk_entry_set_alignment (GTK_ENTRY (caseSudoku[i][j]), 0.5);
      gtk_entry_set_width_chars (GTK_ENTRY (caseSudoku[i][j]), 1);
      gtk_widget_set_size_request (GTK_WIDGET (caseSudoku[i][j]), 40, 40);
      g_signal_connect (caseSudoku[i][j], "focus_out_event", G_CALLBACK (enter_callback), GINT_TO_POINTER(taille));

      if(i % (int)(sqrt(taille)) == 0){ gtk_widget_set_margin_start (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(i % (int)(sqrt(taille)) == (sqrt(taille)-1)){ gtk_widget_set_margin_end (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(j % (int)(sqrt(taille)) == 0){ gtk_widget_set_margin_top (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(j % (int)(sqrt(taille)) == (sqrt(taille)-1)){ gtk_widget_set_margin_bottom (GTK_WIDGET (caseSudoku[i][j]), 5); }

      gtk_grid_attach (GTK_GRID (grilleSudoku), caseSudoku[i][j], i, j, 1, 1);
    }
  }


}
