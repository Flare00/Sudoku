#include "heuristique.h"

size_t heuristiqueFacile(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map)
{
    //A FINIR

    //calculer taille restante;
    size_t casesRestante = 81;
    size_t memoire = 0;
    do
    {
        memoire = casesRestante;
        heuristiqueSingleton(grille, n, bbL, bbC, bbB, map);

        //calculer cases restante.
        casesRestante = 81;
    } while (memoire != casesRestante && casesRestante != 0);

    return casesRestante;
}

size_t heuristiqueMoyenne(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map)
{
    uint8_t modifier = 1;

    //tant que l'algorithme heuristique modifie les cases restante, alors continu.
    while (modifier > 0)
    {
        modifier = 0;
        modifier += heuristiqueJumeauANVisible(grille, n, bbL, bbC, bbB, map);
        modifier += heuristiqueCandidatsIdentique(grille, n, bbL, bbC, bbB, map);
    }

    return heuristiqueFacile(grille, n, bbL, bbC, bbB, map);
}

size_t heuristiqueDifficile(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map)
{
    uint8_t modifier = 1;

    //tant que l'algorithme heuristique modifie les cases restante, alors continu.
    while (modifier > 0)
    {
        modifier = 0;
        modifier += heuristiqueGroupesIsoler(grille, n, bbL, bbC, bbB, map);
        modifier += heuristiqueGroupesMelanger(grille, n, bbL, bbC, bbB, map);
    }

    if (heuristiqueFacile(grille, n, bbL, bbC, bbB, map) > 0)
    {
        return heuristiqueMoyenne(grille, n, bbL, bbC, bbB, map);
    }
    else
    {
        return 0;
    }
}

uint8_t heuristiqueJumeauANVisible(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map)
{
    size_t taille = n * n;
    uint64_t mask = (1 << taille) - 1;

    // bitboard de ligne de bloc correspondant au candidats présent plusieur fois sur la même ligne.
    uint64_t *mbbBL = malloc(n * sizeof(uint64_t));
    // bitboard de colonne de bloc correspondant au candidats présent plusieur fois sur la même colonne.
    uint64_t *mbbBC = malloc(n * sizeof(uint64_t));

    for (size_t bloc = 0; bloc < taille; bloc++)
    {
        for (size_t i = 0; i < n; i++)
        {
            size_t ligne = (bloc / n) + i;
            for (size_t j = 0; j < n; j++)
            {
                size_t colonne = (bloc % n) + i;
                for (size_t k = 0; k < n; k++)
                {
                    mbbBL[i] = mask & (mbbBL[i] | ((~(bbL[ligne] | bbC[colonne] | bbB[((ligne / n) * n) + colonne / n])) & (~(bbL[ligne] | bbC[(bloc % n) + k] | bbB[((ligne / n) * n) + ((bloc % n) + k) / n]))));
                    mbbBC[j] = mask & (mbbBC[j] | ((~(bbL[ligne] | bbC[colonne] | bbB[((ligne / n) * n) + colonne / n])) & (~(bbL[(bloc / n) + k] | bbC[colonne] | bbB[((((bloc / n) + k) / n) * n) + colonne / n]))));
                }
            }
        }

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if (i != j)
                {
                    mbbBL[i] = mask & (mbbBL[i] & ~mbbBL[j]);
                    mbbBC[i] = mask & (mbbBC[i] & ~mbbBC[j]);
                }
            }
        }

        for (size_t i = 0; i < n; i++)
        {
            if (mbbBL[i] != 0)
            {
                //a faire
                //retirer de toute la ligne, sauf case présente, les occurence présente dans mbbBL[i]; 
            }
            if (mbbBC[i] != 0)
            {
                //a faire
            }
        }
    }
}

uint64_t genMbbB(size_t bloc, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (k != j)
                {
                }
            }
        }
    }
}
