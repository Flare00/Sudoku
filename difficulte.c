#include "difficulte.h"
int validiterEtDifficulter(uint8_t **grille, size_t taille, int level)
{
    int retour = 0;

    //si la taille est <= 16 alors 
    if(taille <= 16){
        int n = sqrt(taille);
        uint8_t **map = mapCreer(n);
        if (!map){
            return 0;
        }
        uint32_t *bbL = bitboard32Creer(taille);
        uint32_t *bbC = bitboard32Creer(taille);
        uint32_t *bbB = bitboard32Creer(taille);
        //initialise les bitboard
        bitBoardInitialiser32(grille, n, bbL, bbC, bbB);
        //initialise la liste
        Liste32 *liste = liste32Generer(n,grille, bbL, bbC, bbB, map);
        //si le nombre de resolution est de 1 alors
        if (resolu_32(grille, liste, bbL, bbC, bbB,map, 0, liste->i, liste->j) == 1)
        {
            //determine la difficulté.
            retour = difficulter(grille, taille, level);
        }
        //detruit les elements alloué
        listeDetruire(liste);
        bitBoardDetruire(bbL);
        bitBoardDetruire(bbC);
        bitBoardDetruire(bbB);
        detruire2D(map, taille);
    } else {
        //sinon determine juste la difficulté.
        retour = difficulter(grille, taille, level);
    }
    //detruit la grille temporaire.
    detruire2D(grille, taille);
    return retour;
}

int difficulter(uint8_t **grille, size_t taille, int level)
{
    int retour = 0;
    size_t n = sqrt(taille);

    uint8_t ** map = mapCreer(n);
    //genere la liste
    Liste *liste = listeGenerer(n, grille, map);
    //execute les heurisitque facile
    if (heuristiqueFacile(grille, n, liste, map) == 0)
    {
        //si le niveau eneleve toutes les case retourne le niveau
        retour = 1;
    }
    else
    {
        if (level == 1)
        {
            //sinon si le level choisi est celui la retourne que le niveau est dépassé
            retour = 5;
        }
        else
        {
            //sinon execute les heurisitque Moyenne
            if (heuristiqueMoyenne(grille, n, liste, map) == 0)
            {
                //si le niveau eneleve toutes les case retourne le niveau
                retour = 2;
            }
            else
            {
                if (level == 2)
                {
                    //sinon si le level choisi est celui la retourne que le niveau est dépassé
                    retour = 5;
                }
                else
                {
                    //sinon execute les heurisitque Difficle
                    if (heuristiqueDifficile(grille, n, liste, map) == 0)
                    {
                        //si le niveau eneleve toutes les case retourne le niveau
                        retour = 3;
                    }
                    else
                    {
                        if (level == 3)
                        {
                            //sinon si le level choisi est celui la retourne que le niveau est dépassé
                            retour = 5;
                        }
                        else
                        {
                            //sinon si les heuristique n'on pas résolu l'algorithme mais qu'il est resolvable, alors retourne extreme.
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
    //genere les bitboard, et si réussite alors
    if(bitBoardInitialiser(grille, n, bbL, bbC, bbB) == true){
        //genere la premiere case de la liste, case mémoire vide.
        Liste * liste = NULL;
        Liste * temp = NULL;
        uint64_t mask = (uint64_t)(1<<taille) - 1;

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
                    //pour toute case vide de la grille, genere des elements et les place a la suite de la liste.
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

Liste32 * liste32Generer(size_t n,uint8_t **grille, uint32_t* bbL, uint32_t* bbC, uint32_t* bbB,uint8_t ** map)
{
    size_t taille = n * n;
    Liste32 *retour = NULL;
    Liste32 *prec = NULL;
    Liste32 *liste = NULL;
    uint32_t mask = (uint32_t)(1<<taille) - 1;
    for (size_t i = 0; i < taille; i++)
    {
        size_t tmp = (i / n) * n;
        for (size_t j = 0; j < taille; j++)
        {
            if (grille[i][j] == 0)
            {
                //pour toute les cases du tableau vide, attribut les valeurs dans la liste
                liste = malloc(sizeof(Liste32));
                liste->candidats = mask & (~(bbL[i] | bbC[j] | bbB[map[i][j]]));
                liste->i = i;
                liste->j = j;
                liste->suivante = NULL;
                liste->population = __builtin_popcount(liste->candidats);

                //donne la valeur a c
                liste->c = malloc(liste->population*sizeof(size_t));

                uint32_t candidat = liste->candidats;
                size_t indice = 0;
                size_t p = 0;

                while(candidat)
                {
                    indice = __builtin_ctz(candidat); //Cette méthode intégrée de GCC détermine le nombre de zéros de fin dans la représentation binaire d'un nombre.
                    liste->c[p]= indice;
                    candidat ^= (uint32_t)(1<<indice);
                    p++;
                }       
                //attribut precedente et suivante.
                liste->precedente = prec;
                if(prec != NULL){
                    prec->suivante = liste;
                }
                liste->suivante = NULL;
                prec = liste;
                if(retour == NULL){
                    retour = liste;
                }
                liste = liste->suivante;
            }
        }
    }
    return retour;
}