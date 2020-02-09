/**
* \file doc.h
* \brief Documentation concernant les termes utilisé pour le projet.
*
* __Vocabulaire :__
*	- Un sudoku se défini en NxN cellules tel que 9x9,16x16, 25x25.
*	- ligne et colonne -> sont défini par N cellule aligné (verticalement ou horizontalement).
*	- Bloc ou Région -> sont les groupements de sqrt(N)*sqrt(N) cellules. 
*
*	- Groupe -> correspond a une ligne, colonne ou région.
*	- indice -> valeur déjà inscrite dans la grille à l'initialisation.
*	- candidats -> valeurs possibles pour une cellule donnée.
*
*	- candidats célibataire -> quand il n'y as q'un seul candidat possible.
*	- candidats célibataire caché -> quand il n'es pas le seul candidats pour une cellule, mais que sa présence est unique dans un groupe.
*
* \see http://sudoku.cristallogenese.com/guide/guidesudoku.htm#grid 
*/