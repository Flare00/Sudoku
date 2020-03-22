#include "sudokugtk.h"
#include "interfacegtk.h"

/** Fonction HelloWorld Test **/
void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}

/** Fonction vérification des entrées **/
void enter_callback(GtkWidget *widget, GtkWidget *entry){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

/** Fonction création du Sudoku **/
void sudokuCreer(int taille){
  GtkWidget *caseSudoku[taille][taille];
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  GtkWidget *button4;

  // Grille des Boutons du Jeu
  grilleBoutonJeu = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleBoutonJeu));

  // Boutons exemples
  button1 = gtk_button_new_with_label ("Hello1");
  g_signal_connect (button1, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button1, "clicked", G_CALLBACK (gtk_widget_destroy), fenetre);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (button1), 0, 2, 1, 1);

  button2 = gtk_button_new_with_label ("Hello2");
  g_signal_connect (button2, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button2, "clicked", G_CALLBACK (gtk_widget_destroy), fenetre);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (button2), 1, 2, 1, 1);

  button3 = gtk_button_new_with_label ("Hello3");
  g_signal_connect (button3, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button3, "clicked", G_CALLBACK (gtk_widget_destroy), fenetre);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (button3), 2, 2, 1, 1);

  button4 = gtk_button_new_with_label ("Hello4");
  g_signal_connect (button4, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button4, "clicked", G_CALLBACK (gtk_widget_destroy), fenetre);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (button4), 3, 2, 1, 1);

  // Grille du SUDOKU
  grilleSudoku = gtk_grid_new();
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (grilleSudoku), 0, 0, 4, 2);

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

      if(i % (int)(sqrt(taille)) == 0){ gtk_widget_set_margin_start (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(i % (int)(sqrt(taille)) == (sqrt(taille)-1)){ gtk_widget_set_margin_end (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(j % (int)(sqrt(taille)) == 0){ gtk_widget_set_margin_top (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(j % (int)(sqrt(taille)) == (sqrt(taille)-1)){ gtk_widget_set_margin_bottom (GTK_WIDGET (caseSudoku[i][j]), 5); }

      gtk_grid_attach (GTK_GRID (grilleSudoku), caseSudoku[i][j], i, j, 1, 1);
    }
  }


}
