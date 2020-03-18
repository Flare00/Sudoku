#include "sudokugtk.h"

/** Fonction HelloWorld Test **/
void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}

/** Fonction vérification des entrées **/
static void enter_callback(GtkWidget *widget, GtkWidget *entry){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

/** Fonction création du Sudoku **/
void sudokuCreer(int taille){
  GtkWidget *entry;

  // Construction de la grille
  grilleSudoku = gtk_grid_new ();
  gtk_grid_set_row_homogeneous(GTK_GRID(grilleSudoku), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grilleSudoku), TRUE);

  // Construction du Sudoku
  for (int i=0; i < taille; i++) {
    for (int j=0; j < taille; j++) {
      entry = gtk_entry_new ();
      gtk_entry_set_max_length (GTK_ENTRY (entry), 1);
      gtk_entry_set_text (GTK_ENTRY (entry), "0");
      gtk_entry_set_alignment (GTK_ENTRY (entry), 0.5);
      g_signal_connect (entry, "activate", G_CALLBACK (enter_callback), entry);
      gtk_grid_attach (GTK_GRID (grilleSudoku), entry, i, j, 1, 1);
    }
  }


}
