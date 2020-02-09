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
*
*	---Bitboard---
*	Pour le projet nous utiliserons la technique du Bitboard.
* 	le Bitboard consiste a represent� la pr�sence d'un element dans une ligne, colone ou r�gion, dans une suites de bits.
*	(ex : un ligne 1, ayant un 1, un 4 et un 9. 
*		correspondance	|1|2|3|4|5|6|7|8|9|
*		bits			|1|0|0|1|0|0|0|0|1| 
*		Cette representation ne montre que la pr�sence d'un chiffre, et non son emplacement, sa position pourra �tre retrouv� en utilisant les 3 bitboard, ligne/colonne/r�gion.)
*		
*	Nous utiliserons des valeurs de cellule pouvant aller de 0 � 63. donc des bitboard ayant des valeurs de 64bits.
*	Dans cette configuration nous pouvons r�alis� des sudoku de taille 4x4, 9x9, 16x16, 25x25, 36x36, 49x49, 64x64.
*
*
*
*/

