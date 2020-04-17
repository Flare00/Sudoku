#include "listeGtk.h"

ListeGtk* listeGtkInserer(ListeGtk* liste, int* tab){
  ListeGtk* nouvelle = malloc(sizeof(ListeGtk));
  assert(nouvelle);
  nouvelle->tab = tab;
  nouvelle->suivante = liste;
  return nouvelle;
}

void listeGtkDetruire(ListeGtk* liste){
  while(liste){
    ListeGtk* aSup = liste;
    liste = aSup->suivante;
    if(aSup->tab) free(aSup->tab);
    free(aSup);
  }
  free(liste);
}
