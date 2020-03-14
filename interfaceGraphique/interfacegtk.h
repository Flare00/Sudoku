#ifndef __INTERFACEGTK_H__
#define __INTERFACEGTK_H__

#include <gtk/gtk.h>

typedef struct menu {
  GObject *grilleMenu;
  GObject *etiquetteTitre;
  GObject *boutonJouer;
  GObject *boutonRegles;
  GObject *boutonOptions;
  GObject *boutonQuitter;
} f_Menu;

/** @brief Creer l'interface menu GTK
  * @param f_Menu* leMenu : structure contenant les widgets du menu
  * @return void : affichage */
static void menuCreer(f_Menu *leMenu);

/** @brief Cache l'interface menu GTK
  * @param gpointer data : TODO
  * @param GdkEventButton* event : TODO
  * @param GtkWidget* button : TODO
  * @return gboolean : TODO */
gboolean menuCacher(GtkWidget *button, GdkEventButton *event, gpointer data);


#endif
