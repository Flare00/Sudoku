/**
* \file doc.h
* \brief Documentation concernant les termes utilis� pour le projet.
*
* __Vocabulaire :__
*	- Un sudoku se d�fini en NxN cellules tel que 9x9,16x16, 25x25.
*	- ligne et colonne -> sont d�fini par N cellule align� (verticalement ou horizontalement).
*	- Bloc ou R�gion -> sont les groupements de sqrt(N)*sqrt(N) cellules. 
*
*	- Groupe -> correspond a une ligne, colonne ou r�gion.
*	- indice -> valeur d�j� inscrite dans la grille � l'initialisation.
*	- candidats -> valeurs possibles pour une cellule donn�e.
*
*	- candidats c�libataire -> quand il n'y as q'un seul candidat possible.
*	- candidats c�libataire cach� -> quand il n'es pas le seul candidats pour une cellule, mais que sa pr�sence est unique dans un groupe.
*
* \see http://sudoku.cristallogenese.com/guide/guidesudoku.htm#grid 
*/