#ifndef __INTERFACEGTK_H__
#define __INTERFACEGTK_H__

#include <gtk/gtk.h>

typedef struct menu {
  GObject *fenetre;
  GObject *etiquetteTitre;
  GObject *boutonJouer;
  GObject *boutonRegles;
  GObject *boutonOptions;
  GObject *boutonQuitter;
} f_Menu;

/**
* \brief Création de la fenêtre GTK Menu.
*/
static void menuCreer(f_Menu *leMenu);

/**
* \brief Création de la fenêtre GTK Menu.
*/
static void menuCacher(f_Menu *leMenu);


#endif
