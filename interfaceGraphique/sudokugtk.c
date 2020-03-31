#include "interfacegtk.h"
#include "sudokugtk.h"



/** Fonction envoi du tableau des coordonnées et taille du Sudoku **/
int* envoiCoords(int t, int x, int y){
  int* retour = malloc(3 * (sizeof(int)));
  retour[0] = t;
  retour[1] = x;
  retour[2] = y;
  return retour;
}


/** Fonction vérification du Sudoku **/
void verifSudoku(GtkWidget *widget, gpointer donnee){

  const char *caracDispo[64] = {"1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","@","&","+"};
  int taille = GPOINTER_TO_INT(donnee);
  char trouve;
  uint8_t *tab = malloc(taille*taille*sizeof(uint8_t));
  int idTab = 0;

  for (int i = 0; i < taille; i++){
    for (int j = 0; j < taille; j++){
      trouve = 0;
      if(strcmp("", gtk_entry_get_text(GTK_ENTRY(caseSudoku[j][i]))) == 0){
        tab[idTab] = 0;
        idTab++;
      }
      else{
        for (uint8_t k = 0; k < taille && trouve == 0; k++){
          if(strcmp(caracDispo[k], gtk_entry_get_text(GTK_ENTRY(caseSudoku[j][i]))) == 0){
            trouve = 1;
            tab[idTab] = k+1;
            idTab++;
          }
        }
      }
    }
  }

  if(resoudre(tab, sqrt(taille))){
    printf("RESOLU!\n");
  }
}


/** Fonction vérification Lignes **/
char verifLigne(int t, int l, int c, const char *val){
  char trouve = 0;

  for(int i=0 ; i<t && trouve == 0 ; i++){
    if (i != l) {
      if((strcmp(val, gtk_entry_get_text(GTK_ENTRY(caseSudoku[i][c]))) == 0) && (strcmp("", gtk_entry_get_text(GTK_ENTRY(caseSudoku[i][c]))) != 0)) {
        trouve = 1;
        if(strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[i][c])), "caseBloquee") == 0 ){
          gtk_widget_set_name(caseSudoku[i][c], "caseBloqueErreur");
        }
        else{
          gtk_widget_set_name(caseSudoku[i][c], "caseErreur");
        }
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
      if((strcmp(val, gtk_entry_get_text(GTK_ENTRY(caseSudoku[l][i]))) == 0) && (strcmp("", gtk_entry_get_text(GTK_ENTRY(caseSudoku[l][i]))) != 0)) {
        trouve = 1;
        if(strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[l][i])), "caseBloquee") == 0 ){
          gtk_widget_set_name(caseSudoku[l][i], "caseBloqueErreur");
        }
        else{
          gtk_widget_set_name(caseSudoku[l][i], "caseErreur");
        }
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
        if((strcmp(val, gtk_entry_get_text(GTK_ENTRY(caseSudoku[nI][nJ]))) == 0) && (strcmp("", gtk_entry_get_text(GTK_ENTRY(caseSudoku[nI][nJ]))) != 0)){
          trouve = 1;
          if(strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[nI][nJ])), "caseBloquee") == 0 ){
            gtk_widget_set_name(caseSudoku[nI][nJ], "caseBloqueErreur");
          }
          else{
            gtk_widget_set_name(caseSudoku[nI][nJ], "caseErreur");
          }
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


/** Fonction vérification des entrées en sortie **/
void sortieCase(GtkEntry *widget, GdkEvent *evenement, gpointer donnee){
  // Récupération des arguments
  const gchar *textEntree;
  int* tabCoords = (int*) donnee;

  // Déclatation : Taille - Ligne - Colonne - Caractère de la case
  int taille = tabCoords[0];
  int x = tabCoords[1];
  int y = tabCoords[2];
  textEntree = gtk_entry_get_text (GTK_ENTRY (widget));

  // Réinitialisation CSS des cases
  for(int i=0 ; i<taille ; i++){
    for(int j=0 ; j<taille ; j++){
      if (strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[i][j])), "caseBloqueErreur") == 0 ){
        gtk_widget_set_name(caseSudoku[i][j], "caseBloquee");
      }
      else {
        if (strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[i][j])), "caseBloquee") != 0 ){
          gtk_widget_set_name(caseSudoku[i][j], "caseBase");
        }
      }
    }
  }

  // Vérification : Entree - Ligne - Colonne - Carre
  if(!verifChar(taille, textEntree))  { gtk_entry_set_text (GTK_ENTRY (widget), ""); }
  if(verifLigne(taille, x, y, textEntree)) { gtk_entry_set_text (GTK_ENTRY (widget), ""); }
  if(verifColonne(taille, x, y, textEntree)) { gtk_entry_set_text (GTK_ENTRY (widget), ""); }
  if(verifCarre(taille, x, y, textEntree)) { gtk_entry_set_text (GTK_ENTRY (widget), ""); }
}


/** Fonction surlignement en entrée de case **/
void entreeCase(GtkEntry *widget, GdkEvent *evenement, gpointer donnee){
  // Récupération des arguments
  int* tabCoords = (int*) donnee;

  // Déclatation : Taille - Ligne - Colonne - Caractère de la case
  int taille = tabCoords[0];
  int x = tabCoords[1];
  int y = tabCoords[2];

  // Surlignement Ligne - Colonne
  for(int i=0 ; i<taille ; i++){
    if (i != x) {
      if ((strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[i][y])), "caseErreur") != 0 ) && (strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[i][y])), "caseBloquee") != 0 ) && (strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[i][y])), "caseBloqueErreur") != 0 )){
        gtk_widget_set_name(caseSudoku[i][y], "caseSurligner");
      }
    }
    if (i != y) {
      if ((strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[x][i])), "caseErreur") != 0 ) && (strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[x][i])), "caseBloquee") != 0 ) && (strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[x][i])), "caseBloqueErreur") != 0 )){
        gtk_widget_set_name(caseSudoku[x][i], "caseSurligner");
      }
    }
  }

  // Surlignement Carré
  for(int i=0 ; i<sqrt(taille) ; i++){
    for(int j=0 ; j<sqrt(taille) ; j++){
      int nI = ((int) (((int) (x / sqrt(taille))) * sqrt(taille))) + i;
      int nJ = ((int) (((int) (y / sqrt(taille))) * sqrt(taille))) + j;
      if(!(nI == x && nJ == y)){
        if ((strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[nI][nJ])), "caseErreur") != 0 ) && (strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[nI][nJ])), "caseBloquee") != 0 ) && (strcmp(gtk_widget_get_name (GTK_WIDGET (caseSudoku[nI][nJ])), "caseBloqueErreur") != 0 )){
          gtk_widget_set_name(caseSudoku[nI][nJ], "caseSurligner");
        }
      }
    }
  }
}


/** Remplissage du Sudoku **/
void sudokuRemplir(GtkWidget *grilleSudoku, int taille, int niveau){
  const char *caracDispo[64] = {"1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","@","&","+"};
  size_t t = taille;
  u_int8_t **tableauCases;

  if (niveau != 0){
    tableauCases = genererGrilleSudokuValide(t, niveau);
  }

  for (int i = 0; i < t; i++){
    for (int j = 0; j < t; j++){
      // Création "Entry" - Taille char max - Texte - Align center - Taille pour 1 Char - Taille Carré - Envoi Coords - Signal - Margin - Placement
      caseSudoku[i][j] = gtk_entry_new ();
      gtk_entry_set_max_length (GTK_ENTRY (caseSudoku[i][j]), 1);
      gtk_entry_set_placeholder_text (GTK_ENTRY (caseSudoku[i][j]), "");
      gtk_entry_set_alignment (GTK_ENTRY (caseSudoku[i][j]), 0.5);
      gtk_entry_set_width_chars (GTK_ENTRY (caseSudoku[i][j]), 1);
      gtk_widget_set_size_request (GTK_WIDGET (caseSudoku[i][j]), 40, 40);

      int* tableauCoords = envoiCoords(t, i, j);
      g_signal_connect (caseSudoku[i][j], "focus_in_event", G_CALLBACK (entreeCase), tableauCoords);
      g_signal_connect (caseSudoku[i][j], "focus_out_event", G_CALLBACK (sortieCase), tableauCoords);

      if (niveau != 0){
        if (tableauCases[i][j] != 0){
          gtk_widget_set_sensitive (GTK_WIDGET(caseSudoku[i][j]), FALSE);
          gtk_entry_set_text (GTK_ENTRY (caseSudoku[i][j]), caracDispo[(tableauCases[i][j])-1]);
          gtk_widget_set_name(caseSudoku[i][j], "caseBloquee");
        }
      }

      if(i % (int)(sqrt(t)) == 0){ gtk_widget_set_margin_start (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(i % (int)(sqrt(t)) == (sqrt(t)-1)){ gtk_widget_set_margin_end (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(j % (int)(sqrt(t)) == 0){ gtk_widget_set_margin_top (GTK_WIDGET (caseSudoku[i][j]), 5); }
      if(j % (int)(sqrt(t)) == (sqrt(t)-1)){ gtk_widget_set_margin_bottom (GTK_WIDGET (caseSudoku[i][j]), 5); }

      gtk_grid_attach (GTK_GRID (grilleSudoku), caseSudoku[i][j], i, j, 1, 1);
    }
  }
}



/** Fonction création du Sudoku **/
void sudokuCreer(int taille, int niveau){
  // Widgets
  GtkWidget *grilleBoutonJeu;
  GtkWidget *grilleSudoku;
  GtkWidget *scrollSudoku;
  GtkWidget *jeuRetour;
  GtkWidget *jeuVerification;
  GtkWidget *jeuEtiquetteTitre;

  // Grille de l'interface du Jeu
  grilleBoutonJeu = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (fenetre), GTK_WIDGET (grilleBoutonJeu));

  // Déclatation
  jeuEtiquetteTitre = gtk_label_new ("Sudoku");
  scrollSudoku = gtk_scrolled_window_new (NULL, NULL);
  jeuVerification = gtk_button_new_with_label ("Vérifier");
  jeuRetour = gtk_button_new_with_label ("Retour");

  // CSS
  gtk_widget_set_name(grilleBoutonJeu, "fenetre");
  gtk_widget_set_name(jeuEtiquetteTitre, "titre");
  gtk_widget_set_name(jeuVerification, "bouton");
  gtk_widget_set_name(jeuRetour, "bouton");

  // Expansion
  gtk_container_set_border_width (GTK_CONTAINER (scrollSudoku), 20);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollSudoku), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_set_vexpand (GTK_WIDGET (scrollSudoku), TRUE);
  gtk_widget_set_hexpand (GTK_WIDGET (scrollSudoku), TRUE);

  // Marges
  gtk_widget_set_margin_bottom (GTK_WIDGET (jeuVerification), 10);
  gtk_widget_set_margin_bottom (GTK_WIDGET (jeuRetour), 10);
  gtk_widget_set_margin_start (GTK_WIDGET (jeuRetour), 10);
  gtk_widget_set_margin_end (GTK_WIDGET (jeuVerification), 10);

  // Signaux
  g_signal_connect (jeuVerification, "clicked", G_CALLBACK (verifSudoku), GINT_TO_POINTER(taille));
  g_signal_connect (jeuRetour, "clicked", G_CALLBACK (transitionInterface), grilleMenu);

  // Positionnement
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuEtiquetteTitre), 0, 0, 5, 1);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (scrollSudoku), 0, 1, 5, 2);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuVerification), 4, 3, 1, 1);
  gtk_grid_attach (GTK_GRID (grilleBoutonJeu), GTK_WIDGET (jeuRetour), 0, 3, 1, 1);

  // Grille du Sudoku
  grilleSudoku = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (scrollSudoku), grilleSudoku);
  gtk_widget_set_halign (grilleSudoku, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (grilleSudoku, GTK_ALIGN_CENTER);

  // Construction des cases du Sudoku dans la grille
  sudokuRemplir(grilleSudoku, taille, niveau);
}
