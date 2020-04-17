#ifndef LISTEGTK_H
#define LISTEGTK_H

#include <stdlib.h>
#include <assert.h>

typedef struct listeGtk{
  int* tab;
  struct listeGtk* suivante;
}ListeGtk;

ListeGtk* listeGtkInserer(ListeGtk* liste, int* tab);

void listeGtkDetruire(ListeGtk* liste);

#endif
