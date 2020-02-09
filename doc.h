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
*
*	---Bitboard---
*	Pour le projet nous utiliserons la technique du Bitboard.
* 	le Bitboard consiste a representé la présence d'un element dans une ligne, colone ou région, dans une suites de bits.
*	(ex : un ligne 1, ayant un 1, un 4 et un 9. 
*		correspondance	|1|2|3|4|5|6|7|8|9|
*		bits			|1|0|0|1|0|0|0|0|1| 
*		Cette representation ne montre que la présence d'un chiffre, et non son emplacement, sa position pourra être retrouvé en utilisant les 3 bitboard, ligne/colonne/région.)
*		
*	Nous utiliserons des valeurs de cellule pouvant aller de 0 à 63. donc des bitboard ayant des valeurs de 64bits.
*	Dans cette configuration nous pouvons réalisé des sudoku de taille 4x4, 9x9, 16x16, 25x25, 36x36, 49x49, 64x64.
*
*
*
*/

