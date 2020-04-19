#include "difficulte.h"
int validiterEtDifficulter(uint8_t **grille, size_t taille, int level)
{
    int n = sqrt(taille);
    uint8_t **map = mapCreer(n);
    int retour = 0;
    if (!map)
        return 0;

        

    //if (resolu_64(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map, int count, int pi, int pj) == 1)
    //{
        retour = difficulter(grille, taille, level);
    //}
    grilleDetruire(grille, taille);
    return retour;
}

int difficulter(uint8_t **grille, size_t taille, int level)
{
    int retour = 0;
    size_t n = sqrt(taille);
    uint64_t *bbL = bitboard64Creer(taille);
    uint64_t *bbC = bitboard64Creer(taille);
    uint64_t *bbB = bitboard64Creer(taille);

    bitBoardInitialiser(grille, sqrt(taille), bbL, bbC, bbB);
    uint8_t ** map = mapCreer(n);
    Liste *liste = listeGenerer(n, bbL, bbC, bbB, grille);

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
                    if (heuristiqueDifficile(grille, n, bbL, bbC, bbB, liste,map) == 0)
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

    return retour;
}

Liste* listeGenerer(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **grille)
{
    size_t taille = n * n;

    Liste * retour = NULL;
    Liste * liste = NULL;
    Liste * temp = NULL;

    uint64_t mask = (1<<taille) - 1;

    liste = malloc(sizeof(Liste));
    liste->c = 0;
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
                temp->candidats = mask&(~(bbL[i] | bbC[j] | bbB[tmp+j/n]));
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

    return retour;
}
