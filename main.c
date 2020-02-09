#include "doc.h"
#include <stdint.h>

main(int argc, char * argv[]){
	//Matrice representant un sudoku.
	int8_t sudoku_ex_mat[9][9]={{0,2,0,3,1,7,0,0,0},
								{0,0,0,0,0,9,8,2,1},
								{5,4,0,0,0,0,0,3,0},
								{0,0,9,0,6,2,4,0,3},
								{0,0,0,1,3,0,0,0,6},
								{0,0,7,0,8,4,1,0,2},
								{8,1,0,0,0,0,0,7,0},
								{0,0,0,0,0,1,2,4,8},
								{0,6,0,4,7,8,0,0,0}};
	//chaine de caractère representant le meme sudoku, [0] = N = format du sudoku (NxN); [1 -> 9*9] = valeur de la case correspondant a la coordonnée [(n-1)/9][(n-1)%9];
	char sudoku_ex_str1[(9*9) + 1] = {9,0,2,0,3,1,7,0,0,0,0,0,0,0,0,9,8,2,1,5,4,0,0,0,0,0,3,0,0,0,9,0,6,2,4,0,3,0,0,0,1,3,0,0,0,6,0,0,7,0,8,4,1,0,2,8,1,0,0,0,0,0,7,0,0,0,0,0,0,1,2,4,8,0,6,0,4,7,8,0,0,0}
	return 0;
}