#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "grille.h"
#include "liste.h"
#include "bitBoard.h"

#define bool uint8_t
#define true 1;
#define false 0;
#define block(a, b,n)    (((a/n)*n)+b/n)


bool insertionValide(uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint64_t candidat, uint64_t mask);
void iterativeResolution(size_t taille,size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map, Liste** l1);
bool resolu(uint8_t** grille, Liste *dl, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map);


#endif
