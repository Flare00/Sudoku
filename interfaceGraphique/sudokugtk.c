#include "interfacegtk.h"
#include "sudokugtk.h"

/** Fonction HelloWorld Test **/
void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}


/** Fonction envoi du tableau des coordonnées et taille du Sudoku **/
int* envoiCoords(int t, int x, int y){
  int* retour = malloc(3 * (sizeof(int)));
  retour[0] = t;
  retour[1] = x;
  retour[2] = y;
  return retour;
}


/** Fonction vérification Lignes **/
char verifLigne(int t, int l, int c, const char *val){
  char trouve = 0;

  for(int i=0 ; i<t && trouve == 0 ; i++){
    if (i != l) {
      if(strcmp(val, gtk_entry_get_text(GTK_ENTRY(caseSudoku[i][c]))) == 0) {
        trouve = 1;
      }
    }
  }
  return trouve;
}


/** Fonction vérification Colonnes **/
char verifColonne(int t, int l, int c, const char *val){
  char trouve = 0;

  for(int i=0 ; i<t && trouve == 0 ; i++){
    if (i != c) {
      if(strcmp(val, gtk_entry_get_text(GTK_ENTRY(caseSudoku[l][i]))) == 0) {
        trouve = 1;
      }
    }
  }
  return trouve;
}


/** Fonction vérification Carré **/
char verifCarre(int t, int c, int l, const char *val){
  char trouve = 0;

  for(int i=0 ; i<sqrt(t) && trouve == 0 ; i++){
    for(int j=0 ; j<sqrt(t) && trouve == 0 ; j++){
      int nI = ((int) (((int) (c / sqrt(t))) * sqrt(t))) + i;
      int nJ = ((int) (((int) (l / sqrt(t))) * sqrt(t))) + j;
      if(!(nI == c && nJ == l)){
        if (strcmp(val, gtk_entry_get_text(GTK_ENTRY(caseSudoku[nI][nJ]))) == 0){
          trouve = 1;
        }
      }
    }
  }
  return trouve;
}


/** Fonction vérification Char **/
char verifChar(int t, const char *val){
  char trouve = 0;
  const char *caracDispo[64] = {"1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","@","&","+"};

  for(int i = 0 ; i<t && trouve == 0 ; i++){
    if(strcmp(val, caracDispo[i]) == 0){
      trouve = 1;
    }
  }
  return trouve;
}


/** Fonction vérification des entrées **/
void sortieCase(GtkEntry *widget, GdkEvent *evenement, gpointer donnee){
  // Récupération des arguments
  const gchar *textEntree;
  int* tabCoords = (int*) donnee;

  // Déclatation : Taille - Ligne - Colonne - Caractère de la case
  int taille = tabCoords[0];
  int x = tabCoords[1];
  int y = tabCoords[2];
  textEntree = gtk_entry_get_text (GTK_ENTRY (widget));

  // Vérification : Entree - Ligne - Colonne - Carre
  if(!verifChar(taille, textEntree))  { gtk_entry_set_text (GTK_ENTRY (widget), ""); }
  if(verifLigne(taille, x, y, textEntree)) { gtk_entry_set_text (GTK_ENTRY (widget), ""); }
  if(verifColonne(taille, x, y, textEntree)) { gtk_entry_set_text (GTK_ENTRY (widget), ""); }
  if(verifCarre(taille, x, y, textEntree)) { gtk_entry_set_text (GTK_ENTRY (widget), ""); }
}


/** Fonction création du Sudoku **/
void sudokuCreer(int taille){
  GtkWidget *grilleBoutonJeu;
  GtkWidget *grilleSudoku;
  GtkWidget *scrollSudoku;
  GtkWidget *jeuRetour;
  GtkWidget *jeuVerification;
  GtkWidget *jeuEtiquetteTitre;

  // Grille de l'interface du Jeu
  grilleBoutonJeu = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleBoutonJeu));

  // Widgets
  jeuEtiquetteTitre = gtk_label_new ("Entrez le Sudoku à résoudre");
  scrollSudoku = gtk_scrolled_window_new (NULL, NULL);
  jeuVerification = gtk_button_new_with_label ("Vérification");
  jeuRetour = gtk_button_new_with_label ("Retour Menu");

  gtk_widget_set_name(grilleBoutonJeu, "fenetre");
  gtk_widget_set_name(jeuEtiquetteTitre, "titre");
  gtk_widget_set_name(jeuVerification, "bouton");
  gtk_widget_set_name(jeuRetour, "bouton");

  gtk_container_set_border_width (GTK_CONTAINER (scrollSudoku), 20);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollSudoku), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_set_vexpand (GTK_WIDGET (scrollSudoku), TRUE);
  gtk_widget_set_hexpand (GTK_WIDGET (scrollSudoku), TRUE);

  g_signal_connect (jeuVerification, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (jeuRetour, "clicked", G_CALLBACK (transitionInterface), grilleMenu);

  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuEtiquetteTitre), 0, 0, 5, 1);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (scrollSudoku), 0, 1, 5, 2);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuVerification), 4, 3, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuRetour), 0, 3, 1, 1);



  // Grille du SUDOKU
  grilleSudoku = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (scrollSudoku), grilleSudoku);
  gtk_widget_set_halign (grilleSudoku, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (grilleSudoku, GTK_ALIGN_CENTER);

  // Construction des cases du Sudoku dans la grille
  for (int i = 0; i < taille; i++){
    for (int j = 0; j < taille; j++){
      // Création "Entry" - Taille char max - Texte - Align center - Taille pour 1 Char - Taille Carré - Envoi Coords - Signal - Margin - Placement
      caseSudoku[i][j] = gtk_entry_new ();
      gtk_entry_set_max_length (GTK_ENTRY (caseSudoku[i][j]), 1);
      gtk_entry_set_placeholder_text (GTK_ENTRY (caseSudoku[i][j]), "0");
      gtk_entry_set_alignment (GTK_ENTRY (caseSudoku[i][j]), 0.5);
      gtk_entry_set_width_chars (GTK_ENTRY (caseSudoku[i][j]), 1);
      gtk_widget_set_size_request (GTK_WIDGET (caseSudoku[i][j]), 40, 40);

      int* tableauCoords = envoiCoords(taille, i, j);
      g_signal_connect (caseSudoku[i][j], "focus_out_event", G_CALLBACK (sortieCase), tableauCoords);

      if(i % (int)(sqrt(taille)) == 0){ gtk_widget_set_margin_start (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(i % (int)(sqrt(taille)) == (sqrt(taille)-1)){ gtk_widget_set_margin_end (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(j % (int)(sqrt(taille)) == 0){ gtk_widget_set_margin_top (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(j % (int)(sqrt(taille)) == (sqrt(taille)-1)){ gtk_widget_set_margin_bottom (GTK_WIDGET (caseSudoku[i][j]), 5); }

      gtk_grid_attach (GTK_GRID (grilleSudoku), caseSudoku[i][j], i, j, 1, 1);
    }
  }
}
