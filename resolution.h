#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "grille.h"
#include "liste.h"
#include "bitBoard.h"

#define bool uint8_t
#define true 1;
#define false 0;
#define block(a, b,n)    (((a/n)*n)+b/n)

uint8_t** creerMap(size_t n);

bool insertionValide(uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint64_t candidat, uint64_t mask);
void iterativeResolution(size_t taille,size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map, Liste** l1);

bool insertionValide_32(uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint32_t candidat, uint32_t mask);
void iterativeResolution_32(size_t taille, size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t** grille, uint8_t** map,Liste** l1);

uint64_t *rotationBoard(size_t taille,uint64_t *bb);

void trouvehiddenpair(size_t taille,Liste *dl,uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t**map);
bool searchListe (size_t taille,Liste *dl, Liste*dl2,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t**map);
void trouveCandidatCache(size_t taille,uint8_t** grille,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map);

bool resolu(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map);
bool resolu_32(uint8_t** grille, Liste *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t **map);


#endif
