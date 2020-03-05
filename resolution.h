#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "grille.h"
#include "liste.h"

#define bool uint8_t
#define true 1;
#define false 0;

int valeurBit(uint64_t bits, size_t indice);

bool resolu(uint8_t** grille, Liste *dl, size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB);

#endif