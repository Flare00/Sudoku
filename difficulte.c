#include "difficulte.h"
int validiterEtDifficulter(uint8_t **grille, size_t taille, int level)
{
    int retour = 0;
    
    if(taille <= 16){
        int n = sqrt(taille);
        uint8_t **map = mapCreer(n);
        if (!map){
            return 0;
        }
        uint32_t *bbL = bitboard32Creer(taille);
        uint32_t *bbC = bitboard32Creer(taille);
        uint32_t *bbB = bitboard32Creer(taille);

        bitBoardInitialiser32(grille, n, bbL, bbC, bbB);
        Liste32 *liste = listeGenerer32(n, bbL, bbC, bbB, grille, map);

        if (resolu_32(grille, liste, bbL, bbC, bbB,map, 0, liste->i, liste->j) == 1)
        {
            retour = difficulter(grille, taille, level);
        }
        
        listeDetruire(liste);
        bitBoardDetruire(bbL);
        bitBoardDetruire(bbC);
        bitBoardDetruire(bbB);
        detruire2D(map, taille);
    } else {
        retour = difficulter(grille, taille, level);

    }
    detruire2D(grille, taille);
    return retour;
}

int difficulter(uint8_t **grille, size_t taille, int level)
{
    int retour = 0;
    size_t n = sqrt(taille);

    uint8_t ** map = mapCreer(n);

    Liste *liste = listeGenerer(n, grille, map);

    if (heuristiqueFacile(grille, n, liste, map) == 0)
    {
        retour = 1;
    }
    else
    {
        if (level == 1)
        {

            retour = 5;
        }
        else
        {
            if (heuristiqueMoyenne(grille, n, liste, map) == 0)
            {
                retour = 2;
            }
            else
            {
                if (level == 2)
                {
                    retour = 5;
                }
                else
                {
                    if (heuristiqueDifficile(grille, n, liste,map) == 0)
                    {
                        retour = 3;
                    }
                    else
                    {
                        if (level == 3)
                        {
                            retour = 5;
                        }
                        else
                        {
                            retour = 4;
                        }
                    }
                }
            }
        }
    }

    while(liste != NULL){
        Liste * temp = liste;
        liste = liste->suivante;
        free(temp);
    }

    detruire2D(map,taille);

    return retour;
}

Liste* listeGenerer(size_t n,uint8_t **grille,uint8_t ** map)
{
    size_t taille = n * n;

    Liste * retour = NULL;


    uint64_t *bbL = bitboard64Creer(taille);
    uint64_t *bbC = bitboard64Creer(taille);
    uint64_t *bbB = bitboard64Creer(taille);
    if(bitBoardInitialiser(grille, n, bbL, bbC, bbB) == true){
        Liste * liste = NULL;
        Liste * temp = NULL;
        uint64_t mask = (1<<taille) - 1;

        liste = malloc(sizeof(Liste));
        liste->c = NULL;
        liste->candidats = 0;
        liste->i = 0;
        liste->j = 0;
        liste->population = 0;
        liste->precedente = NULL;
        liste->suivante = NULL;
        retour = liste;

        for (size_t i = 0; i < taille; i++)
        {
            size_t tmp = (i / n) * n;
            for (size_t j = 0; j < taille; j++)
            {
                if (grille[i][j] == 0)
                {

                	temp = malloc(sizeof(Liste));
                    temp->c = NULL;
                    temp->candidats = mask & (~(bbL[i] | bbC[j] | bbB[map[i][j]]));
                    temp->i = i;
                    temp->j = j;
                    temp->suivante = NULL;
                    temp->population = __builtin_popcount(temp->candidats);
                    temp->precedente = liste;
                    liste->suivante = temp;
                    liste = liste->suivante;
                }
            }
        }
        free(bbL);
        free(bbC);
        free(bbB);
    }
    return retour;
}

Liste32* listeGenerer32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t **grille, uint8_t ** map)
{
    size_t taille = n * n;

    Liste32 * liste = NULL;
    Liste32 * temp = NULL;

    uint32_t mask = (1<<taille) - 1;

    liste = malloc(sizeof(Liste32*));
    temp = liste;
    for (size_t i = 0; i < taille; i++)
    {
        size_t tmp = (i / n) * n;
        for (size_t j = 0; j < taille; j++)
        {
            if (grille[i][j] == 0)
            {
                if(temp == NULL){
                    temp = malloc(sizeof(Liste32*));
                }
                
                temp->c = NULL;
                temp->candidats = mask&(~(bbL[i] | bbC[j] | bbB[map[i][j]]));
                temp->i = i;
                temp->j = j;
                temp->population = __builtin_popcount(temp->candidats);
                temp->suivante = malloc(sizeof(Liste32*));
                temp->suivante->precedente = temp;
                temp = temp->suivante;
            }
        }
    }

    return liste;
}
