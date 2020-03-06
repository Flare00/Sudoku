#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "grille.h"
#include "liste.h"
#include "bitBoard.h"

#define bool uint8_t
#define true 1;
#define false 0;

int valeurBit(uint64_t bits, size_t indice);
int insertionValide(uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint64_t candidat, uint64_t mask);
void res(size_t taille,size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, Liste** l1);

bool resolu(uint8_t** grille, Liste *dl, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB);
uint8_t firstBitPosition(size_t taille, size_t min, uint64_t bitWord);

#endif
